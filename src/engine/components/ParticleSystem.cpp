#include "ParticleSystem.h"

void ParticleSystem::ShotAll() {
	for (int i = 0; i < Limit; i++)
		spawnParticle();
}

void ParticleSystem::Update() {
	float dt = ofGetLastFrameTime();
	currentSpawnRate += dt;

	for (int i = 0; i < particles.size(); i++) {
		particles[i].forces += Turbulence;
		particles[i].scale = ofNormalize(particles[i].scale, 0, FinalScale);
		particles[i].scale += dt;
		particles[i].Update();

		if (particles[i].currentLifeTime >= LifeTime)
			destroyParticle();
	}

	if (ofGetLastFrameTime() > 1 || !Enable)
		return;

	if (currentSpawnRate >= SpawnRate) {
		if (particles.size() > Limit)
			destroyParticle();

		currentSpawnRate = 0;
		spawnParticle();
	}
}

void ParticleSystem::spawnParticle() {
	Particle p = Particle();
	p.position = gameObject->transform.position;
	p.scale = InitialScale;
	p.forces = InitialForces;
	float x = ofRandomf();
	float y = ofRandomf();
	float z = ofRandomf();
	p.forces += vec3(x, y, z) * RandomForces;
	particles.push_back(p);
}

void ParticleSystem::destroyParticle() {
	particles.erase(particles.begin());
}

void ParticleSystem::Draw() {
	loadVBO();

	ofEnableDepthTest();
	Shader.begin();
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	vbo.draw(GL_POINTS, 0, (int)particles.size());
	Shader.end();
	ofDisableDepthTest();
}

void ParticleSystem::loadVBO() {
	vector<vec3> sizes;
	vector<vec3> points;
	for (int i = 0; i < particles.size(); i++) {
		vec3 position = particles[i].position + Origin;
		if (!WorldSpace)
			position = gameObject->transform.position + Origin;

		points.push_back(position);
		sizes.push_back(vec3(particles[i].scale));
	}

	int total = (int)points.size();
	vbo.clear();
	vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
	vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
}

mat4 ParticleSystem::matrix4(int particle) {
	mat4 matrix = mat4();

	mat4 scale4 = glm::scale(mat4(1.0), vec3(particles[particle].scale));
	matrix = scale4;
	return matrix;
}