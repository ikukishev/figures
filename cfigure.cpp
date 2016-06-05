#include "cfigure.h"

CFigure::CFigure(std::shared_ptr<CPolygon> basis, const std::string &name)
    :mNameFigure(name), mMat(glm::mat4(1)), mBasis(basis)
{}

CFigure::~CFigure() {}

void CFigure::setMatrix(const glm::mat4 &mat) { mMat=mat; }

glm::mat4 CFigure::getMatrix() const {return mMat;}

glm::vec3 CFigure::operator[](Uint index) const {
    glm::vec4 vec(getCalculatedVertex(index), 1.0);
    vec =mMat*vec;
    return glm::vec3(vec.x, vec.y, vec.z);
}

const std::string CFigure::type() const {return "class CFigure";}

std::string CFigure::getName() const {return mNameFigure;}

void CFigure::setName(const std::string &name) { mNameFigure=name;}

std::shared_ptr<CPolygon> CFigure::getBasis() const
{
    return mBasis;
}

void CFigure::setBasis(const std::shared_ptr<CPolygon> &basis)
{
    mBasis = basis;
}

double CFigure::distance(glm::vec3 a, glm::vec3 b) const
{
    return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y)+(b.z-a.z)*(b.z-a.z));
}

double CFigure::calculatedArea(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c) const
{
    double pPer = (distance(a, b)+distance(b, c)+distance(c, a))/2.0;
    return sqrt((pPer*(pPer-distance(a,b))*(pPer-distance(b,c)))*(pPer-distance(c,a)));
}
