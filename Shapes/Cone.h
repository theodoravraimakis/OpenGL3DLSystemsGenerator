//
// Created by Theodora Vraimakis on 14/02/2023.
//

#ifndef FINALYEARPROJECT_CONE_H
#define FINALYEARPROJECT_CONE_H

#include "Mesh.h"

class Cone : public Shape {
public:
    Cone(
            bool cap,
            float length,
            int count,
            glm::vec3 color,
            glm::mat4 transformations
            );
    Cone();
    void make() override;

protected:

private:
    friend class UI;
    friend class Render;
};


#endif //FINALYEARPROJECT_CONE_H
