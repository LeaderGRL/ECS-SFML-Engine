#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>

namespace LeaderEngine
{
	class CameraComponent : IComponent
	{
	private :
		sf::View view;
		sf::Vector2f position;
		sf::Vector2f size;
		float rotation;
		float zoom;

	public:
		CameraComponent();
		~CameraComponent();

		sf::View getView();
		void setView(sf::View view);

		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f position);

		sf::Vector2f getSize();
		void setSize(sf::Vector2f size);

		float getRotation();
		void setRotation(float rotation);

		float getZoom();
		void setZoom(float zoom);

		void Update() override;
	};
}