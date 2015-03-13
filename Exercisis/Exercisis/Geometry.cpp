#include "Geometry.h"


Geometry::Geometry()
{
	data = vector<Vertex>(0);
}


Geometry::~Geometry()
{
	data.clear();
}

void Geometry::loadScene(const char *fname) {
	data = vector<Vertex>(0);
	ifstream myfile;
	myfile.open(fname);
	int n, v, f, v0, v1, v2, rgba0, rgba1, rgba2, rgba3;
	float xv, yv, zv,sx,sy,sz,ra,rx,ry,rz,tx,ty,tz;
	vector<glm::vec3> vertices;
	vector<glm::u32vec3> faces;
	myfile >> n;
	for (int i = 0; i < n; ++i) {
		myfile >> v;
		vertices = vector<glm::vec3>(v);
		for (int j = 0; j < v; ++j) {
			myfile >> xv >> yv >> zv;
			vertices[j] = { xv, yv, zv };
		}
		myfile >> f;
		faces = vector<glm::u32vec3>(f);
		for (int j = 0; j < f; ++j) {
			myfile >> v0 >> v1 >> v2;
			faces[j] = { v0, v1, v2 };
		}
		myfile >> sx >> sy >> sz;
		glm::vec3 scalation = { sx, sy, sz };
		myfile >> ra >> rx >> ry >> rz;
		glm::vec3 rotation = { rx, ry, rz };
		myfile >> tx >> ty >> tz;
		glm::vec3 translation = { tx, ty, tz };
		for (int j = 0; j < v; ++j) {
			//cout <<"a"<< vertices[j].x << " " << vertices[j].y << " " << vertices[j].z << endl;
			vertices[j] *= scalation;
			//cout << vertices[j].x << " " << vertices[j].y << " " << vertices[j].z << endl;
			glm::rotate(vertices[j], glm::radians(ra), rotation);
			//cout << vertices[j].x << " " << vertices[j].y << " " << vertices[j].z << endl;
			vertices[j] += translation;
			//cout << vertices[j].x << " " << vertices[j].y << " " << vertices[j].z << endl;
		}
		myfile >> rgba0 >> rgba1 >> rgba2 >> rgba3;
		for (int j = 0; j < f; ++j) {
			int id0, id1, id2;
			id0 = faces[j].x - 1;
			id1 = faces[j].y - 1;
			id2 = faces[j].z - 1;
			Vertex v0,v1,v2;
			v0.setPosition(vertices[id0].x, vertices[id0].y, vertices[id0].z);
			v0.setColor(rgba0, rgba1, rgba2, rgba3);
			v1.setPosition(vertices[id1].x, vertices[id1].y, vertices[id1].z);
			v1.setColor(rgba0, rgba1, rgba2, rgba3);
			v2.setPosition(vertices[id2].x, vertices[id2].y, vertices[id2].z);
			v2.setColor(rgba0, rgba1, rgba2, rgba3);
			data.push_back(v0);
			data.push_back(v1);
			data.push_back(v2);
		}
	}
}

vector<Vertex> Geometry::getData() {
	cout << "LOG DATA1" << endl;
	for (int i = 0; i < data.size(); ++i) {
		cout << i << endl;
		cout << data[i].position.x << " " << data[i].position.y << " " << data[i].position.z << endl;
		cout << data[i].color.r << " " << data[i].color.g << " " << data[i].color.b << " " << data[i].color.a << endl;
	}
	return data;
}