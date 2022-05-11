#include "TerrainCollider.h"

void TerrainCollider::Init(int levels) {
	Mesh* meshComponent = gameObject->GetComponent<Mesh>();
	if (meshComponent == NULL) {
		cout << "Mesh component is required for TerrainCollider" << endl;
		return;
	}

	this->levels = levels;
	mesh = meshComponent->getMesh();
	cout << "Terrain vertices: " << mesh.getNumVertices() << endl;
	debugLevel = levels;
	int level = 0;
	root.aabb = AABB::MeshBounds(mesh);

	if (!bUseFaces) {
		for (int i = 0; i < mesh.getNumVertices(); i++) {
			root.points.push_back(i);
		}
	}

	level++;
	Subdivide(mesh, root, levels, level);
}

void TerrainCollider::Subdivide(const ofMesh& mesh, TreeNode& node, int levels, int level) {
	if (level >= levels) return;

	vector<AABB> childs;
	SubDivideAABB8(node.aabb, childs);
	vector<TreeNode> all;
	all.resize(childs.size());

	for (int i = 0; i < childs.size(); i++) {
		all[i].aabb = childs[i];
		if (GetMeshPointsInBox(mesh, node.points, all[i].aabb, all[i].points) > 0) {
			node.children.push_back(all[i]);
		}
	}

	if (node.children.size() > 0) {
		for (int i = 0; i < node.children.size(); i++) {
			if (node.children[i].points.size() > 1)
				Subdivide(mesh, node.children[i], levels, level + 1);
		}
	}

	return;
}

void TerrainCollider::SubDivideAABB8(const AABB& aabb, vector<AABB>& aabbList) {
	vec3 min = aabb.parameters[0];
	vec3 max = aabb.parameters[1];
	vec3 size = max - min;
	vec3 center = size / 2 + min;

	float xdist = (max.x - min.x) / 2;
	float ydist = (max.y - min.y) / 2;
	float zdist = (max.z - min.z) / 2;
	vec3 h = vec3(0, ydist, 0);

	AABB b[8];
	b[0] = AABB(min, center);
	b[1] = AABB(b[0].Min() + vec3(xdist, 0, 0), b[0].Max() + vec3(xdist, 0, 0));
	b[2] = AABB(b[1].Min() + vec3(0, 0, zdist), b[1].Max() + vec3(0, 0, zdist));
	b[3] = AABB(b[2].Min() + vec3(-xdist, 0, 0), b[2].Max() + vec3(-xdist, 0, 0));

	aabbList.clear();
	for (int i = 0; i < 4; i++) {
		aabbList.push_back(b[i]);
	}

	for (int i = 4; i < 8; i++) {
		b[i] = AABB(b[i - 4].Min() + h, b[i - 4].Max() + h);
		aabbList.push_back(b[i]);
	}
}

int TerrainCollider::GetMeshPointsInBox(const ofMesh& mesh, const vector<int>& points, AABB& aabb, vector<int>& pointsRtn) {
	int count = 0;
	for (int i = 0; i < points.size(); i++) {
		ofVec3f v = mesh.getVertex(points[i]);
		if (aabb.Inside(vec3(v.x, v.y, v.z))) {
			count++;
			pointsRtn.push_back(points[i]);
		}
	}
	return count;
}

void TerrainCollider::DrawNode(TreeNode& node, int level) {
	if (level >= levels) return;

	DrawAABB(node.aabb);
	level++;

	for (int i = 0; i < node.children.size(); i++) {
		DrawNode(node.children[i], level);
	}
}

void TerrainCollider::DrawAABB(const AABB& aabb) {
	vec3 min = aabb.parameters[0];
	vec3 max = aabb.parameters[1];
	vec3 size = max - min;
	vec3 center = size / 2 + min;
	ofVec3f p = ofVec3f(center.x, center.y, center.z);
	float w = size.x;
	float h = size.y;
	float d = size.z;
	ofDrawBox(p, w, h, d);
}

void TerrainCollider::Draw() {
	if (!Physics::showColliders)
		return;

	ofDisableLighting();
	ofEnableDepthTest();
	ofPushMatrix();
	ofNoFill();
	ofSetColor(ofColor::green);
	DrawLevel(debugLevel);
	ofPopMatrix();
	ofDisableDepthTest();
	ofEnableLighting();
}