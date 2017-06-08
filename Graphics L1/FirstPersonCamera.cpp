#include "FirstPersonCamera.h"


FirstPersonCamera::FirstPersonCamera()
{
	this->Reset(0, 0, 1,
		0, 0, 0,
		0, 1, 0);

	SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
}


FirstPersonCamera::~FirstPersonCamera()
{
}
FirstPersonCamera::FirstPersonCamera(std::unique_ptr<FirstPersonCamera> tmp)
{
	this->mDirection = -tmp->GetLookDirection();
	this->mPosition = tmp->GetEyePosition();
	this->mProjectionMatrix = tmp->GetProjectionMatrix();
	this->mRight = tmp->mRight;
	this->mUp = tmp->mUp;
	this->mViewMatrix = tmp->GetViewMatrix();
}

vec3 FirstPersonCamera::GetLookDirection()
{
	return -mDirection;
}

void FirstPersonCamera::Reset(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	vec3 eyePt(eyeX, eyeY, eyeZ);
	vec3 centerPt(centerX, centerY, centerZ);
	vec3 upVec(upX, upY, upZ);

	this->Reset(eyePt, centerPt, upVec);
}

void FirstPersonCamera::Reset(const vec3 &eye, const vec3 &center, vec3 &up)
{
	mPosition = eye;

	mDirection = normalize(mPosition - center);
	mRight = normalize(cross(up, mDirection));
	mUp = normalize(cross(mDirection, mRight));

	this->UpdateViewMatrix();
}

mat4 FirstPersonCamera::GetViewMatrix()
{
	return mViewMatrix;
}

void FirstPersonCamera::UpdateViewMatrix()
{
	vec3 mCenter = mPosition + this->GetLookDirection();
	mViewMatrix = lookAt(mPosition, mCenter, mUp);
}

mat4 FirstPersonCamera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}

void FirstPersonCamera::SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far)
{
	mProjectionMatrix = perspective(FOV, aspectRatio, near, far);
}

void FirstPersonCamera::Slide(float stepR, float stepU, float stepD)
{
	mPosition += stepR * mRight;
	mPosition += stepU * mUp;
	mPosition += stepD * this->GetLookDirection();
}

void FirstPersonCamera::Yaw(float angleDegrees)
{
	mDirection = glm::rotate(mDirection, angleDegrees, mUp);
	mRight = glm::rotate(mRight, angleDegrees, mUp);
}

bool FirstPersonCamera::Pitch(float angleDegrees)
{
	mUp = glm::vec3(0,1,0);
	vec3 temp = glm::rotate(mDirection, angleDegrees, mRight);
	temp *= -1;
	vec3 lookY = temp;
	lookY.y = 0;
	if (glm::dot(temp, lookY) > 0.75)
	{
		mDirection = -temp;
		return 1;
	}
	else return 0;
}

void FirstPersonCamera::Roll(float angleDegrees)
{
	mRight = glm::rotate(mRight, angleDegrees, mDirection);
	mUp = glm::vec3(0, 1, 0);
}

void FirstPersonCamera::Walk(float dist)
{
	vec3 mCenter =this->mPosition + this->GetLookDirection();
	vec3 walkdir = vec3(mCenter.x, this->mPosition.y, mCenter.z) - this->mPosition;

	mPosition += dist * walkdir;
}

void FirstPersonCamera::Strafe(float dist)
{
	vec3 mR = this->mPosition + mRight;

	vec3 strafedir = vec3(mR.x, mPosition.y, mR.z) - mPosition;
	mPosition += dist *strafedir;
}

void FirstPersonCamera::Fly(float dist)
{
	mPosition += dist * mUp;
}

glm::vec3 FirstPersonCamera::GetEyePosition()
{
	return mPosition;
}

void FirstPersonCamera::CheckWalls()
{
	int maxx = 995.7;
	int maxy = 995.7;
	vec3 Position = this->GetEyePosition();
	if (Position.x > maxx)
		this->mPosition.x = maxx;
	else if (Position.x < -maxx)
		this->mPosition.x = -maxx;

	if (Position.y > maxy)
		this->mPosition.y = maxy;
	else if (Position.y < -maxy)
		this->mPosition.y = -maxy;

	if (Position.z > maxx)
		this->mPosition.z = maxx;
	else if (Position.z < -maxx)
		this->mPosition.z = -maxx;
}

