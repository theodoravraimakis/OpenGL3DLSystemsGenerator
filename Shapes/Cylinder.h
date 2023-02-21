//
// Created by Theodora Vraimakis on 12/02/2023.
//

#ifndef FINALYEARPROJECT_CYLINDER_H
#define FINALYEARPROJECT_CYLINDER_H

#include "Mesh.h"


class Cylinder : public Shape {
public:
    Cylinder(
            bool cap,
            float diameter,
            int count,
            glm::vec3 color,
            glm::mat4 transformations
    );
    Cylinder();
    void make() override;
};


#endif //FINALYEARPROJECT_CYLINDER_H
