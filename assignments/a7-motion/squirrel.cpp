#include "atkui/framework.h"
#include <map>

using namespace agl;
using namespace atk;
using namespace glm;

struct Sprite {
    std::string name;
    float rotation;
    vec3 position;
    vec3 pivot;
    Image image;
};

class Squirrel : public atkui::Framework {

public:
    Squirrel() : atkui::Framework(atkui::Orthographic) {}

    virtual void setup() {
        loadSprite("body", vec3(0.5, 0.5f, 0.0f), 0, "../models/squirrel/squirrel-body.png");
        loadSprite("tail", vec3(0.5, 0.1f, 0.0f), 0, "../models/squirrel/squirrel-tail.png");
        loadSprite("arm1", vec3(0.3, 0.9f, 0.0f), 0.3, "../models/squirrel/squirrel-arm.png");
        loadSprite("arm2", vec3(0.3, 0.9f, 0.0f), 0, "../models/squirrel/squirrel-arm.png");
        loadSprite("leg1", vec3(0.3, 0.9f, 0.0f), 0, "../models/squirrel/squirrel-leg.png");
        loadSprite("leg2", vec3(0.3, 0.9f, 0.0f), 0, "../models/squirrel/squirrel-leg.png");
        renderer.blendMode(agl::BLEND);
        background(vec3(0.8));

        _sprites["tail"].position = vec3(-50, -100, 0);
        _sprites["leg2"].position = vec3(-50, -100, 0);
        _sprites["leg1"].position = vec3(0, -100, 0);
        _sprites["arm1"].position = vec3(-50, -50, 0);
        _sprites["arm2"].position = vec3(50, -50, 0);
        _sprites["body"].position = vec3(-100, -200, 0);
    }

    virtual void scene() {
        drawShadow();
    
        const Sprite& body = _sprites["body"];
        const Sprite& arm1 = _sprites["arm1"];
        const Sprite& arm2 = _sprites["arm2"];
        const Sprite& leg1 = _sprites["leg1"];
        const Sprite& leg2 = _sprites["leg2"];
        const Sprite& tail = _sprites["tail"];

        push();
        translate(vec3(width()*0.5, height()*0.65, 0));
        rotate(body.rotation, vec3(0,0,1));

        // arm1
        push();
        Transform ta1 = Transform(
            glm::angleAxis(arm1.rotation, vec3(0, 0, 1)), arm1.position
        );
        transform(ta1);
        translate(-arm1.pivot);
        drawSprite(arm1);
        pop();

        // leg2
        push();
        Transform tl2 = Transform(
            glm::angleAxis(leg2.rotation, vec3(0, 0, 1)), leg2.position
        );
        transform(tl2);
        translate(-leg2.pivot);
        drawSprite(leg2);
        pop();


        // body
        push();
        translate(body.position);
        //translate(-body.pivot);
        drawSprite(body);
        pop();
    
        // leg1
        push();
        Transform tl1 = Transform(
            glm::angleAxis(leg1.rotation, vec3(0, 0, 1)), leg1.position
        );
        transform(tl1);
        translate(-leg1.pivot);
        drawSprite(leg1);
        pop();
    
        // arm2
        push();
        Transform ta2 = Transform(
            glm::angleAxis(arm2.rotation, vec3(0, 0, 1)), arm2.position
        );
        transform(ta2);
        translate(-arm2.pivot);
        drawSprite(arm2);
        pop();

        // todo tail
        push();
        Transform tt = Transform(
            glm::angleAxis(tail.rotation, vec3(0, 0, 1)), tail.position
        );
        transform(tt);
        translate(-tail.pivot);
        drawSprite(tail);
        pop();

        pop(); 


        renderer.fontColor(vec4(0,0,0,1));
        drawText("Selected: "+_selected, 5, 25);
    }

    void drawSprite(const Sprite& sprite) {
        renderer.beginShader("sprite2d");
        renderer.texture("image", sprite.name);
        scale(vec3(sprite.image.width(), sprite.image.height(), 1));
        renderer.sprite(sprite.pivot, vec4(1.0f), 1.0f); 
        renderer.endShader();
    }

    void loadSprite(const std::string& name, const vec3& pivotOffset, float startRot, const std::string& filename) 
    {
        Image image;
        bool success = image.load(filename, true);

        if (success) {
            renderer.loadTexture(name, image, 1);
            vec3 pivot = vec3(image.width(), image.height(), 0) * pivotOffset;
            _sprites[name] = Sprite{name,startRot, vec3(0), pivot, image};

            std::cout << "load " << name << ": (" << image.width() << ", " << image.height() 
            << ") pivot: " << glm::to_string(pivot) << std::endl;

        } else {
            std::cout << "Error: cannot load " << filename << std::endl;
        }
    }

    void drawShadow() {
        setColor(vec3(0.75));
        push();
        translate(vec3(width()*0.5, height()*0.05, -300));
        scale(vec3(1,0.1, 0.1));
        drawSphere(vec3(0), 300);
        pop();
    }

    void keyUp(int keyChar, int mods) 
    {
        int key = keyChar - '1'; // convert char to integer
        if (key >= 0 && key < _sprites.size()) {
            auto it = _sprites.begin();
            for (int i = 0; i < key; i++) it++;
            _selected = it->first;
        } 
        //std::cout << "selected: " << keyChar << " " << key << " " << _selected << std::endl;

        if (keyChar == GLFW_KEY_UP) {
            _sprites[_selected].rotation += 0.1;
        } else if (keyChar == GLFW_KEY_DOWN) {
            _sprites[_selected].rotation -= 0.1;
        }


        Sprite& s = _sprites[_selected];
        switch (keyChar)
        {
        case GLFW_KEY_W:
        {
            s.position += vec3(0, 50, 0);
            std::cout << _selected << ": " << s.position.x << ": " << 
                s.position.y << ": " << s.position.z << ": " << std::endl;
            break;
        }
        case GLFW_KEY_S:
        {
            s.position += vec3(0, -50, 0);
            std::cout << _selected << ": " << s.position.x << ": " <<
                s.position.y << ": " << s.position.z << ": " << std::endl;
            break;
        }
        case GLFW_KEY_A:
        {
            s.position += vec3(-50, 0, 0);
            std::cout << _selected << ": " << s.position.x << ": " <<
                s.position.y << ": " << s.position.z << ": " << std::endl;
            break;
        }
        case GLFW_KEY_D:
        {
            s.position += vec3(50, 0, 0);
            std::cout << _selected << ": " << s.position.x << ": " <<
                s.position.y << ": " << s.position.z << ": " << std::endl;
            break;
        }
        }

    }

private:
    std::string _selected = "arm1";
    std::map<std::string, Sprite> _sprites;
    Skeleton _skeleton;
};

int main(int argc, char** argv) {
    Squirrel viewer;
    viewer.run();
}
