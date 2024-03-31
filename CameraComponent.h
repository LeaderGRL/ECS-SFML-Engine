#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>

namespace LeaderEngine
{
	class CameraComponent : public IComponent
	{
	private :
		sf::View _view;
		sf::Vector2f _position;
		sf::Vector2f _size;
		float _rotation;
		float _zoom;

	public:
		CameraComponent();
		//CameraComponent(sf::FloatRect);
		~CameraComponent();

		sf::View getView();
		void setView(const sf::View& view);

		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f position);

		sf::Vector2f getSize();
		void setSize(const sf::Vector2f& size);

		float getRotation();
		void setRotation(float rotation);

		float getZoom();
		void setZoom(float zoom);

		void Init() override;
		void Update(float deltaTime) override;

		COMPONENT_TYPE GetType() const override;
	};
}