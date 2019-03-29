#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

string axis[] = {"x","y","z"};

float xmin = -3;
float xmax = 3;
float ymin = -2;
float ymax = 8;
float zmin = 0;
float zmax = 32;
float z = 1;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;
const int BEHIND = 16;
const int TOOCLOSE = 32;

//data structure for x,y,z is an array from 0 to 2
void Print3Vector(vector<int> point, vector<int> by, vector<int> r){
    
    for (int i = 0; i < 3; i++) {
                cout << "Translate Point "+axis[i]+": "+ to_string(point[i]) << " By "+axis[i]+": "+ to_string(by[i]) << " Result "+axis[i]+": "+ to_string(r[i]) << endl;
    }
}

void Print3Vector(vector<float> point, vector<float> by, vector<float> r, string type){
    
    for (int i = 0; i < 3; i++) {
        cout << type + " " + axis[i]+": "+ to_string(point[i]) << " By "+axis[i]+": "+ to_string(by[i]) << " Result "+axis[i] + ": "+ to_string(r[i]) << endl;
    }
}

void Print2Vector(vector<float> point, vector<float> r, string type)
{
    for (int i = 0; i < 3; i++) {
        cout << type + " " + axis[i]+": "+ to_string(point[i]) << " To: " << " Result "+axis[i] + ": "+ to_string(r[i]) << endl;
    }
}

void PrintRotate(vector<float> point, float theta, vector<float> r){
    
        cout << "Rotate Point "+to_string(point[0])  +","+to_string(point[1])+","+to_string(point[2])+": " << " By "+to_string(theta) << " Result : "+to_string(r[0])  +","+to_string(r[1])+","+to_string(r[2])+ ": " << endl;
}

void PointsToScalar(vector<float> a, vector<float> b, float scalar, string type)
{
    for (int i = 0; i < 3; i++) {
        cout <<  axis[i]+": "+ to_string(a[i]) << " By: " << axis[i] + ": "+ to_string(b[i]) << endl;
    }
    
    cout << type + " Scalar: " + to_string(scalar) << endl;
}

void PrintOutcode(int code)
{
    cout<< "The Outcode is: ";
    switch (code) {
        case 0:
            cout << "000000"<< endl;
            break;
        case 1:
            cout << "100000"<< endl;
            break;
        case 2:
            cout << "010000"<< endl;
            break;
        case 4:
            cout << "001000"<< endl;
            break;
        case 8:
            cout << "000100"<< endl;
            break;
        case 16:
            cout << "000010"<< endl;
            break;
        case 32:
            cout << "000001"<< endl;
            break;
        default:
            break;
    }
}

// Geometric Operations
vector<float> Translate(vector<float> point, vector<float> translation)
{
    vector<float> ab(3);
    for (int i = 0; i < 3; i++)
    {
        ab[i] = point[i] + translation[i];
    }
    return ab;
}

void TranslatePoint()
{
    vector<float> point = {4,5,6};
    vector<float> translation = {1,2,3};
    string type = "Translate Point";
    cout << type << endl;
    Print3Vector(point, translation,Translate(point, translation),type);
}

vector<float> RotateXAxis(vector<float> point, float theta)
{
    vector<float> ab(3);
    
    ab[0] = point[0];
    ab[1] = point[1]*cos(theta) - point[2] * sin(theta);
    ab[2] = point[1]*sin(theta) + point[2]*cos(theta);
    
    return ab;
}

void RotateX()
{
    vector<float> point = {4,5,6};
    float theta = 43;
    cout << "Rotate Point X Axis"<< endl;
    PrintRotate(point, theta, RotateXAxis(point, theta));

}

vector<float> RotateYAxis(vector<float> point, float theta)
{
    vector<float> ab(3);
    
    ab[0] = point[2]*sin(theta) + point[0]*cos(theta);
    ab[1] = point[1];
    ab[2] = point[2]*cos(theta) - point[0]*sin(theta);
    
    return ab;
}

void RotateY()
{
    vector<float> point = {4,5,6};
    float theta = 43;
    cout << "Rotate Point Y Axis"<< endl;
    PrintRotate(point, theta, RotateYAxis(point, theta));
}

vector<float> RotateZAxis(vector<float> point, float theta)
{
    vector<float> ab(3);
    
    ab[0] = point[0]*cos(theta) - point[1]*sin(theta);
    ab[1] = point[0]*sin(theta) + point[1]*cos(theta);
    ab[2] = point[2];
    
    return ab;
}

void RotateZ()
{
    vector<float> point = {4,5,6};
    float theta = 43;
    cout << "Rotate Point Z Axis"<< endl;
    PrintRotate(point, theta, RotateZAxis(point, theta));
}

vector<float> Scale(vector<float> point, vector<float> translation)
{
    vector<float> ab(3);
    for (int i = 0; i < 3; i++)
    {
        ab[i] = point[i] * translation[i];
    }
    return ab;
}

void ScalePoint()
{
    vector<float> point = {4,5,6};
    vector<float> scalingFactor = {1,2,3};
    string type = "Scale Point";
    cout << type << endl;
    Print3Vector(point, scalingFactor,Scale(point, scalingFactor),type);
}

vector<float> Project(vector<float> point, float d)
{
    vector<float> ab(3);
    
    ab[0] = point[0]/(point[2]/d);
    ab[1] = point[1]/(point[2]/d);
    ab[2] = point[2];

    return ab;
}

void ProjectPoint()
{
    vector<float> point = {4,5,6};
    float d = 4.5;
    string type = "Project Point";
    cout << type << endl;
    Print2Vector(point, Project(point, d), type);
}




// Clipping Operations
int CohenSutherlandPoint(vector<float> point)
{
    // initialized as being inside
    int code = INSIDE;
        
    if (point[0] < xmin)       // left
            code |= LEFT;
        else if (point[0] > xmax)  // right
            code |= RIGHT;
        if (point[1] < ymin)       // below
            code |= BOTTOM;
        else if (point[1] > ymax)  // above
            code |= TOP;
    if (point[2] < zmin)
        code |= BEHIND;
    else if (point[2] > zmax)
        code |= TOOCLOSE;
    
        
        return code;
}

void CohenSutherland()
{
    vector<float> point = {1,1,1};
    PrintOutcode(CohenSutherlandPoint(point));
}

bool AcceptLine(vector<float> a, vector<float> b)
{
//    cout << to_string(CohenSutherlandPoint(a)) <<endl;
//    cout << to_string(CohenSutherlandPoint(b)) <<endl;
    int result = CohenSutherlandPoint(a) | CohenSutherlandPoint(b);
    
    if(result == 0)
        return true;
    return false;
}

bool DiscardLine(vector<float> a, vector<float> b)
{
    //    cout << to_string(CohenSutherlandPoint(a)) <<endl;
    //    cout << to_string(CohenSutherlandPoint(b)) <<endl;
    int result = CohenSutherlandPoint(a) & CohenSutherlandPoint(b);
    
    if(result != 0)
        return true;
    return false;
}

bool ClipLine(vector<float> a , vector<float> b)
{
    //    cout << to_string(CohenSutherlandPoint(a)) <<endl;
    //    cout << to_string(CohenSutherlandPoint(b)) <<endl;
    if(AcceptLine(a, b) == false && DiscardLine(a, b) == false)
        return true;
    return false;
}

void CohenSutherlandAcceptDiscardClip()
{
    vector<float> a = {1,1,1};
    vector<float> b = {1,2,1};

    if(AcceptLine(a, b) == 1)
        cout << "This line is accepted" << endl;
    else
        cout << "This line is not accepted" << endl;
    
    if(DiscardLine(a, b) == 1)
        cout << "This line is discarded" << endl;
    else
        cout << "This line is not discarded" << endl;
    
    if(ClipLine(a, b) == 1)
        cout << "This line is clipped" << endl;
    else
        cout << "This line is not clipped" << endl;
}

// Shading Operations
float MagnitudeOfVector(vector<float> point)
{
    return sqrt((point[0] * point[0]) + (point[1] * point[1]) + (point[2] * point[2]));
}

vector<float> DifferenceBetweenVectors(vector<float> a , vector<float> b)
{
    vector<float> ab(3);
    ab[0] = a[0]-b[0];
    ab[1] = a[1]-b[1];
    ab[2] = a[2]-b[2];
    
    return ab;
}

vector<float> MultiplyVectorbyScalar(float scalar, vector<float> v)
{
    vector<float> ab(3);
    for (int i = 0; i < 3; i++) {
        ab[i] = scalar * v[i];
    }
    
    return ab;
}

vector<float> Normalize(vector<float> point)
{
    vector<float> ab(3);
    float magnitude = MagnitudeOfVector(point);
    ab[0] = point[0]/magnitude;
    ab[1] = point[1]/magnitude;
    ab[2] = point[2]/magnitude;
    
    return ab;
}

void NormalizeLength()
{
    vector<float> point = {4,5,6};
    string type = "Normalize Length";
    cout << type << endl;
    Print2Vector(point,Normalize(point),type);
}

float CalculateDotProduct(vector<float> a, vector<float> b)
{
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

void DotProduct()
{
    vector<float> a = {4,5,6};
    vector<float> b = {1,2,3};
    string type = "Dot Product";
    cout << type << endl;
    PointsToScalar(a, b, CalculateDotProduct(a, b), type);
}

vector<float> CalculateCrossProduct(vector<float> a, vector<float> b)
{
    vector<float> ab(3);
    ab[0] = a[1] * b[2] - (a[2] * b[1]);
    ab[1] = a[2] * b[0] - (a[0] * b[2]);
    ab[2] = a[0] * b[1] - a[1] * b[0];
    return ab;
}

void CrossProduct()
{
    vector<float> a = {4,5,6};
    vector<float> b = {1,2,3};
    string type = "Cross Product";
    cout << type << endl;
    Print3Vector(a, b, CalculateCrossProduct(a, b), type);
}

float CalculateDiffuseTerm(float kd, vector<float> a, vector<float> b, float intensity)
{
    return kd * CalculateDotProduct(a, b) * intensity;
}

void DiffuseTerm()
{
    float kd = 0.3;
    float intensity = 5;
    vector<float> a = {4,5,6};
    vector<float> b = {1,2,3};
    string type = "Diffuse Term";
    cout << type << endl;
    PointsToScalar(a, b, CalculateDiffuseTerm(kd, Normalize(a), Normalize(b), intensity), type);
}

vector<float> CalculateIdealReflection( vector<float> l, vector<float> n)
{
    vector<float> ab(3);
    ab = DifferenceBetweenVectors(MultiplyVectorbyScalar(2 * CalculateDotProduct(l, n), n), l);
    return ab;
}

void IdealReflection()
{
    vector<float> a = {4,5,6};
    vector<float> b = {1,2,3};
    string type = "Ideal Reflection";
    cout << type << endl;
    Print3Vector(a, b, CalculateIdealReflection(Normalize(a),Normalize(b)), type);
}

float CalculateSpecularTerm(float ks, vector<float> a, vector<float> b, float intensity, float shininess)
{
    return ks * pow(CalculateDotProduct(a, b),shininess) * intensity;
}

void SpecularTerm()
{
    float ks = 0.3;
    float intensity = 5;
    float shininess = 0.2;
    vector<float> a = {4,5,6};
    vector<float> b = {1,2,3};
    string type = "Specular Term";
    cout << type << endl;
    PointsToScalar(a, b, CalculateSpecularTerm(ks, Normalize(a), Normalize(b), intensity, shininess), type);
}

int main(int argc, char *argv[])
{
    TranslatePoint();
    RotateX();
    RotateY();
    RotateZ();
    ScalePoint();
    ProjectPoint();
    CohenSutherland();
    CohenSutherlandAcceptDiscardClip();
    NormalizeLength();
    DotProduct();
    CrossProduct();
    DiffuseTerm();
    IdealReflection();
    SpecularTerm();
}

