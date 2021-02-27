#pragma once

#include <c4d_string.h>

namespace st::qc::ModelProperties
{
	enum class PropertyTypes
	{
		NONE,
		EyeBall
	};

	class ModelProperty
	{
	public:
		ModelProperty() = default;
		virtual ~ModelProperty() = default;

		virtual PropertyTypes GetType() = 0;
	};

	struct ModelPropertyEyeball : public ModelProperty
	{
		ModelPropertyEyeball(String name)
			: Name(name), EyeballCenter(), YawOffset(0.0f) { }

		PropertyTypes GetType() override { return PropertyTypes::EyeBall; }

		String Name;
		String ParentBoneName;
		Vector EyeballCenter;
		String MaterialName;
		Float YawOffset;
	};
}