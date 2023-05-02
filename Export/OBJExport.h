//
// Created by Theodora Vraimakis on 12/03/2023.
//

#ifndef FINALYEARPROJECT_OBJEXPORT_H
#define FINALYEARPROJECT_OBJEXPORT_H

#include "../Shapes/Mesh.h"
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <rapidobj/rapidobj.hpp>

#include "../Error/Error.h"
#include "glm/glm.hpp"


class OBJExport {

public:
    static bool exportToOBJ(const MeshData& meshData, std::string& fileName);
    static MeshData loadOBJ(const std::string& fileName);
    static GLuint loadTexture(const std::string& fileName, int desiredChannels);
};


#endif //FINALYEARPROJECT_OBJEXPORT_H
