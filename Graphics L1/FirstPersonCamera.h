#ifndef FirstPersonCamera_h__
#define FirstPersonCamera_h__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include<memory>
using namespace glm;

class FirstPersonCamera
{
public:
	vec3 mUp;
	vec3 mRight;
	vec3 mDirection;
	mat4 mViewMatrix;
	mat4 mProjectionMatrix;

	vec3 GetLookDirection();

	FirstPersonCamera(void);
	FirstPersonCamera(std::unique_ptr<FirstPersonCamera>);
	~FirstPersonCamera(void);

	vec3 mPosition;
	void UpdateViewMatrix();
	mat4 GetViewMatrix();
	void SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far);
	mat4 GetProjectionMatrix();
	vec3 GetEyePosition();

	void Reset(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
	void Reset(const vec3 &eye, const vec3 &center, vec3  &up);
	void CheckWalls();

#pragma region Rotations
	/// <summary>
	/// Rotates the axes (N, R) about the U-axis with the specified angle. This is equivalent to
	/// a left-turn.
	/// </summary>//y--->z--->x
	void Yaw(float angleDegrees);

	/// <summary>
	/// Rotates the axes (U, N) about the R-axis with the specified angle. This is equivalent
	/// to a look-up (up turn).
	/// </summary>//x--->y--->z
	bool Pitch(float angleDegrees);

	/// <summary>
	/// Rotates the axes (R, U) about the N-axis with the specified angle.
	/// </summary>//z--->x--->y
	void Roll(float angleDegrees);
#pragma endregion

#pragma region Translations

	/// <summary>
	/// Moves the eye point a distance dist forward == -dist * N
	/// Walk
	/// </summary>
	void Walk(float dist);

	/// <summary>
	/// Moves the eye point a distance dist to the right == +dist * R
	/// Strafe
	/// </summary>
	void Strafe(float dist);

	/// <summary>
	/// Moves the eye point a distance dist upward == +dist * U
	/// Fly
	/// </summary>
	void Fly(float dist);

#pragma endregion

	/// <summary>
	/// Moves the eye position a distance stepR along the vector R,
	/// a distance stepU along the vector U, and a distance stepD
	/// along the vector N.
	/// </summary>
	void Slide(float stepR, float stepU, float stepD);
};
#endif // FirstPersonCamera_h__