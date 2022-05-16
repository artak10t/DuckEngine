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
	ofEnableDepthTest();
	Shader.begin();
	for (int i = 0; i < particles.size(); i++) {
		if (i >= particles.size())
			break;

		ofPushMatrix();
		ofMultMatrix(matrix4(i));
		ofDrawSphere(vec3(0), 1);
		ofPopMatrix();
	}
	Shader.end();
	ofDisableDepthTest();
}

mat4 ParticleSystem::matrix4(int particle) {
	mat4 matrix = mat4();
	mat4 translate4 = translate(mat4(1.0), particles[particle].position + Origin);

	if(!WorldSpace)
		translate4 = translate(mat4(1.0), gameObject->transform.position + Origin);

	mat4 scale4 = glm::scale(mat4(1.0), vec3(particles[particle].scale));
	matrix = translate4 * scale4;
	return matrix;
}