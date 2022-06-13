using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParabolicMotion 
{
	enum Mode
	{
		DistanceTime,
		SpeedAngle
	}
	Mode mode;

	float gravity;
	float startY;
	float startAngle;
	float distance;
	float time;
	Vector2 startVelocity;

	float Sec(float x)
	{
		return 1f / Mathf.Cos(x);
	}

	public ParabolicMotion(float distance, float time, float startY, float gravity = 9.81f)
	{
		mode = Mode.DistanceTime;

		this.gravity = gravity;
		this.startY = startY;
		this.distance = distance;
		this.time = time;

		startVelocity = new Vector2(
			distance / time,
			(0.5f * gravity * Mathf.Pow(time, 2f) - startY) / time
			);
	}

	public ParabolicMotion(Vector2 startVelocity, float startY, float gravity = 9.81f)
	{
		mode = Mode.SpeedAngle;

		this.startVelocity = startVelocity;
		this.gravity = gravity;
		this.startY = startY;

		Vector2 startDir = startVelocity.normalized;
		startAngle = Mathf.Atan2(startDir.y, startDir.x);
	}

	float GetA()
	{
		switch (mode)
		{
			case Mode.DistanceTime:
				return -0.5f * gravity;
			case Mode.SpeedAngle:
				return -(gravity / (2f * Mathf.Pow(startVelocity.magnitude, 2f) * Mathf.Pow(Mathf.Cos(startAngle), 2f)));
		}

		return 0;
	}

	float GetB()
	{
		switch (mode)
		{
			case Mode.DistanceTime:
				return startVelocity.y;

			case Mode.SpeedAngle:
				return Mathf.Tan(startAngle);
		}

		return 0;
	}

	float GetC()
	{
		switch (mode)
		{
			case Mode.DistanceTime:
				return startY;

			case Mode.SpeedAngle:
				return startY;
		}

		return 0;
	}

	float GetDelta()
	{
		return Mathf.Pow(GetB(), 2f) - 4f * GetA() * GetC();
	}

	public float Evaluate(float x)
	{
		switch(mode)
		{
			case Mode.DistanceTime:
				float ti = x / startVelocity.x;
				return GetA() * Mathf.Pow(ti, 2f) + GetB() * ti + GetC();

			case Mode.SpeedAngle:
				return GetA() * Mathf.Pow(x, 2f) + GetB() * x + GetC();
		}

		return 0;
	}

	public float GetDistance()
	{
		switch(mode)
		{
			case Mode.DistanceTime:
				return distance;

			case Mode.SpeedAngle:
				float tmp = (2f * gravity * startY * Mathf.Pow(Sec(startAngle), 2f)) / Mathf.Pow(startVelocity.magnitude, 2f) + Mathf.Pow(Mathf.Tan(startAngle), 2f);
				return -(Mathf.Pow(startVelocity.magnitude, 2f) * Mathf.Pow(Mathf.Cos(startAngle) ,2f) * ( -Mathf.Tan(startAngle) - Mathf.Sqrt(tmp) ))/ gravity;
		}

		return 0;
	}

	public float GetTime()
	{
		switch(mode)
		{
			case Mode.DistanceTime:
				return time;

			case Mode.SpeedAngle:
				return GetDistance() / startVelocity.x;
		}

		return 0;
	}

	public float GetMaxHeight()
	{
		return -GetDelta() / (4f * GetA());
	}
}
