INDX( 	 �']�           (   8   �         xi
>glm  :ds[                    Ѭ    n j&$j��j&$j��j&$j��j&$j��                "       l o c k                     Ѭ    n $�qj���m�"j���m�"j���m�"j��                      s c . u s e r _ i n j e c t e d . 1 . e t l                 Ѭ    n $�qj���m�"j���m�"j���m�"j��                      S C U S E R ~ 1 . E T L                     Ѭ    n )y�"j��Y�"j��Y�"j��Y�"j��                      S C U S E R ~ 2 . E T L                    Ѭ    n )y�"j��Y�"j��Y�"j��Y�"j��                      S C U S E R ~ 2 . E T L                          //Joint* root = new Joint("root");
        //root->setLocalTranslation(vec3(width() / 2.0f, height() - height() / 3.0f, 0));
        //root->setLocalRotation(glm::angleAxis(angle, vec3(0, 0, 1)));
        //skeleton.addJoint(root);

        //Joint* j1 = new Joint("joint1");
        //j1->setLocalTranslation(vec3(0, -75, 0));
        //j1->setLocalRotation(glm::angleA s(angle1, vec3(0, 0, 1)));
        //skeleton.addJoint(j1, root);

        //Joint* j2 = new Joint("joint2");
        //j2->setLocalTranslation(vec3(0, -75, 0));
        //skeleton.addJoint(j2, j1);
        //skeleton.fk();

        angle = glm::pi<float>() / 2.0f;
        Transform root = Transform(
            glm::angleAxis(angle, vec3(0, 0, 1)), vec3(vec3(width() / 2.0f, height() - height() / 3.0f, 0))
        );
        transforms["root"] = root;
        angle1 = glm::pi<float>() / 2.0f;         Transform p1 = root * Transform(
            glm::angleAxis(angle1, vec3(0, 0, 1)), vec3(0.0f, -75.0f, 0.0f)
        );
        transforms["point1"] = p1;
        position1 = p1.t();
        Transform p2 = p1 * Transform(
            glm::angleAxis(0.0f, vec3(0)), vec3(0.0f, -75.0f, 0.0f)
        );
        transforms["point2"] = p2;
        position2 = p2.t();
    }

    virtual void scene() 
    {
        setColor(vec3(1, 0, 0));


        //vec3 rt = skeleton.getByName("root")- etGlobalTranslation();
        //vec3 j1t = skeleton.getByName("joint1")->getGlobalTranslation();
        //vec3 j2t = skeleton.getByName("joint2")->getGlobalTranslation();
        //vec3 d = glm::normalize(rt - j1t);
        //vec3 d1 = glm::normalize(j1t - j2t);

        //dangle += glm::dot(vec3(0, -1, 0), glm::cross(d, vec3(0, 0, 1))) * dt();
        //angle += dangle * dt();
        //skeleton.getByName("root")->setLocalRotation(glm::angleAxis(angle, vec3(0, 0, 1)));

        //dangle1 += g ::dot(vec3(0, -1, 0), glm::cross(d1, vec3(0, 0, 1))) * dt();
        //angle1 += dangle1 * dt();
        //skeleton.getByName("joint1")->setLocalRotation(glm::angleAxis(angle1, vec3(0, 0, 1)));

        //skeleton.fk();

        vec3 rt = transforms["root"].t();
        vec3 p2t = transforms["point2"].t();
        vec3 p1t = transforms["point1"].t();

        vec3 d = glm::normalize(p1t - rt);
        vec3 d1 = glm::normalize(p2t - p1t);
        vec3 tangent1 = glm::cross(d, vec3(0, 0, 1));
       vec3 tangent2 = glm::cross(d1, vec3(0, 0, 1));

        //vec3 a1 = glm::dot(-tangent1, vec3(0, -1, 0)) * tangent1;
        //vec3 a2 = (glm::dot(-tangent2, vec3(0, -1, 0)) * glm::dot(d, d1) * tangent2 +
        //    vec3(0, -1, 0) * glm::dot(tangent1, tangent2));

        //velocity1 += a1 * dt();
        //velocity2 += a2 * dt();
        //position1 += velocity1 * dt();
        //position2 += velocity2 * dt();

        dangle1 += std::tan(1 / glm::length(d1)) * dt() * 
            glm: ot(tangent2, vec3(0, 1, 0));
        angle1 += dangle1 * dt();

        dangle += std::tan(1 / glm::length(d)) * dt() * glm::dot(tangent1, vec3(0, 1, 0));
        angle += dangle * dt();



        transforms["root"].setR(glm::angleAxis(angle, vec3(0, 0, 1)));
        transforms["point1"] = transforms["root"] *
            Transform(glm::angleAxis(0.0f, vec3(0)), vec3(0, -75, 0));
        transforms["point1"].setR(glm::angleAxis(angle1, vec3(0, 0, 1)));
        transforms["point2"] = transform "point1"] *
            Transform(glm::angleAxis(0.0f, vec3(0)), vec3(0, -75, 0));


        drawSphere(transforms["root"].t(), 10);
        drawLine(transforms["root"].t(), transforms["point1"].t());
        drawSphere(transforms["point1"].t(), 10);
        drawLine(transforms["point1"].t(), transforms["point2"].t());
        drawSphere(transforms["point2"].t(), 10);
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
            sprites[name] = Sprite{ name,startRot, vec3(0), pivot, image };

            std::cout << "load " << name << ": (" << image.width() << ", " << image.height()
                << ") pivot: " << glm::to_string(pivot) << std::endl;

        }
        else {
            std::cout << "Error: cannot load " << filename << std::endl;
        }
    }

    void keyUp(int keyChar, int mods)
    {
        int key = keyChar - '1'; // convert char to integer
        if (key >= 0 && key < sprites.size()) {
            auto it = sprites.begin();
            for (int i = 0; i < key; i++) it++;
            selected = it->first;
        }
        //std::cout << "selected: " << keyChar << " " << key << " " << selected << std::endl;

        if (keyChar == GLFW_KEY_UP) {
            sprites[selected].rotation += 0.1;
        }
        else if (keyChar == GLFW_KEY_DOWN) {
            sprites[selected].rotation -= 0.1;
        }


        Sprite& s = sprites[selected];
        switch (keyChar)
        {
        case GLFW_KEY_W:
        {
            s.position += vec3(0, 50, 0);
            std::cout << selected << ": " << s.position.x << ": " <<
                s.position.y << ": " << s.position.z << ": " << std::endl;
            break;
        }
        case GLFW_KEY_S:
        {
            s.position += vec3(0, -50, 0);
            std::cout << selected << ": " << s.position.x << ": " <<
                s.position.y << ": " << s.position.z << ": " << std::endl;
            break;
        }
        case GLFW_KEY_A:
        {
            s.position += vec3(-50, 0, 0);
            std::cout << selected << ": " << s.position.x << ": " <<
                s.position.y << ": " << s.position.z << ": " << std::endl;
            break;
        }
        case GLFW_KEY_D:
        {
            s.position += vec3(50, 0, 0);
            std::cout << selected << ": " << s.position.x << ": " <<
                s.position.y << ": " << s.position.z << ": " << std::endl;
            break;
        }
        }

    }

private:
    std::string selected = "arm1";
    std::map<std::string, Sprite> sprites;

    std::map<std::string, Transform> transforms;
    Skeleton skeleton;

    float angle = 0.0f;
    float dangle = 0.0f;

    float angle1 = 0.0f;
    float dangle1 = 0.0f;

    vec3 velocity1 = vec3(0), velocity2 = vec3(0);
    vec3 position1, position2;

};

int main(int argc, char** argv) {
    Unique viewer;
    viewer.run();
}
