#pragma once

#include "tiny_obj_loader.h"


#pragma mark -
#pragma mark Interface

namespace ofxTinyObjLoader
{
	typedef struct
	{
		string name;
		ofMesh mesh;
		ofMaterial material;
		string material_name;
		
		void draw(bool useMaterial=true)
		{
			if (useMaterial) material.begin();
			mesh.draw();
			if (useMaterial) material.end();
		}
		
	} Shape;
	
	ofMesh toOf(tinyobj::mesh_t shape);
	ofMaterial toOf(tinyobj::material_t material);
	
	vector<Shape> load(const string filename, bool dump=true);
};


#pragma mark -
#pragma mark Implementation

vector<ofxTinyObjLoader::Shape> ofxTinyObjLoader::load(const string filename, bool dump)
{
	vector<ofxTinyObjLoader::Shape> of_shapes;
	
	vector<tinyobj::shape_t> shapes;
	
	string basepath = ofToDataPath("./");
	string err = tinyobj::LoadObj(shapes, ofToDataPath(filename).c_str(), basepath.c_str());
	
	if (!err.empty())
	{
		ofLogError("ofxTinyObjLoader") << err;
		return of_shapes;
	}

	for (size_t i = 0; i < shapes.size(); i++)
	{
		ofxTinyObjLoader::Shape shape;
		shape.name = shapes[i].name;
		shape.mesh = toOf(shapes[i].mesh);
		shape.material = toOf(shapes[i].material);
		shape.material_name = shapes[i].material.name;
//		cout << shape.name << endl;
//		cout << shape.material_name << endl;
//		cout << "-----------" << endl;
		
		of_shapes.push_back(shape);
	}

	return of_shapes;
}

ofMesh ofxTinyObjLoader::toOf(tinyobj::mesh_t mesh)
{
	ofMesh of_mesh;
	
	assert(mesh.positions.size() %3 == 0);
	
	for (int i=0; i<mesh.positions.size(); i+=3)
	{
		const ofVec3f v(mesh.positions[i + 0],
						mesh.positions[i + 1],
						mesh.positions[i + 2]);
		
//		cout << "position:" << v << endl;
		
		of_mesh.addVertex(v);
	}
	
	
	assert(mesh.normals.size() %3 == 0);
	
	for (int i=0; i<mesh.normals.size(); i+=3)
	{
		const ofVec3f n(mesh.normals[i + 0],
						mesh.normals[i + 1],
						mesh.normals[i + 2]);
		
//		cout << "normal:" << n << endl;
		
		of_mesh.addNormal(n);
	}
	
	
	assert(mesh.texcoords.size() %2 == 0);
	
	for (int i=0; i<mesh.texcoords.size(); i+=2)
	{
		const ofVec2f t(mesh.positions[i + 0],
						mesh.positions[i + 1]);
		
//		cout << "texcoord:" << t << endl;
		
		of_mesh.addTexCoord(t);
	}
	
	
	for (int i=0; i<mesh.indices.size(); i+=1)
	{
		const ofIndexType index = (ofIndexType)mesh.indices[i];
		
//		cout << "index:" << index << endl;
		
		of_mesh.addIndex(index);
	}
	
	return of_mesh;
}

ofMaterial ofxTinyObjLoader::toOf(tinyobj::material_t material)
{
	ofMaterial of_material;
	
	
	ofFloatColor ambient(material.ambient[0],
						 material.ambient[1],
						 material.ambient[2]);
	
//	cout << "ambient:" << ambient << endl;
	of_material.setAmbientColor(ambient);
	
	
	ofFloatColor diffuse(material.diffuse[0],
						 material.diffuse[1],
						 material.diffuse[2]);
	
//	cout << "diffuse:" << diffuse << endl;
	of_material.setDiffuseColor(diffuse);
	
	
	ofFloatColor specular(material.specular[0],
						  material.specular[1],
						  material.specular[2]);
	
//	cout << "specular:" << specular << endl;
	of_material.setSpecularColor(specular);
	
	
	ofFloatColor emission(material.emission[0],
						  material.emission[1],
						  material.emission[2]);
	
//	cout << "emission:" << emission << endl;
	of_material.setEmissiveColor(emission);
	
	
	float shininess = material.shininess;
	
//	cout << "shininess:" << shininess << endl;
	of_material.setShininess(shininess);
	

	// ...we don't load the following stuffs
	/*
    std::string name;

    float transmittance[3];
    float ior;                // index of refraction
	
    std::string ambient_texname;
    std::string diffuse_texname;
    std::string specular_texname;
    std::string normal_texname;
    std::map<std::string, std::string> unknown_parameter;
	 */
	
	return of_material;
}