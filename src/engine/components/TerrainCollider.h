#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../Physics.h"
#include "../AABB.h"
#include "Mesh.h"
#include <ofGraphics.h>
#include <gl/ofLight.h>
#include <graphics/of3dGraphics.h>

/*
    Terrain is divide into octree nodes where each
    node has a child.
*/
class TreeNode {
public:
    TreeNode() {}

    AABB aabb;
    vector<int> points;
    vector<TreeNode> children;
};

class TerrainCollider : public Component
{
public:
    using Component::Component;
    TreeNode root;
    bool bUseFaces = false;
    // Show octree level
    int debugLevel = 0;

    // Check if intersected with AABB
    bool IntersectAABB(const AABB& aabb, TreeNode& node, vector<AABB>& aabbList);

    // Check if intersected with Ray
    bool IntersectRay(const Ray& ray, TreeNode& node, TreeNode& nodeList);

    // Creates octree with the given levels
    void Init(int levels);
    void Draw();

private:
    void Subdivide(const ofMesh& mesh, TreeNode& node, int levels, int level);
    void SubDivideAABB8(const AABB& aabb, vector<AABB>& aabbList);
    int GetMeshPointsInBox(const ofMesh& mesh, const vector<int>& points, AABB& aabb, vector<int>& pointsRtn);
    void DrawNode(TreeNode& node, int level);
    void DrawLevel(int level) { DrawNode(root, level); };
    void DrawAABB(const AABB& aabb);

    int levels;
    ofMesh mesh;
};

