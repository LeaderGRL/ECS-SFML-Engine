#include "pch.h"
#include "CameraComponent.h"
#include <iostream>

using namespace std;

namespace LeaderEngine
{
	CameraComponent::CameraComponent()
	{
		
	}

	CameraComponent::~CameraComponent()
	{
		
	}
	
	sf::View CameraComponent::getView()
	{
		return view;
	}
	
	void CameraComponent::setView(sf::View view)
	{
		this->view = view;
	}
	
	sf::Vector2f CameraComponent::getPosition()
	{
		return position;
	}
	
	void CameraComponent::setPosition(sf::Vector2f position)
	{
		this->position = position;
	}
	
	sf::Vector2f CameraComponent::getSize()
	{
		return sf::Vector2f();
	}
	
	void CameraComponent::setSize(sf::Vector2f size)
	{
		this->size = size;
	}
	
	float CameraComponent::getRotation()
	{
		return rotation;
	}
	
	void CameraComponent::setRotation(float rotation)
	{
		this->rotation = rotation;
	}
	
	float CameraComponent::getZoom()
	{
		return zoom;
	}
	
	void CameraComponent::setZoom(float zoom)
	{
		this->zoom = zoom;
	}
	
	void CameraComponent::Update(float deltaTime)
	{
		view.setCenter(position);
		view.setRotation(rotation);
		view.setSize(size);
		view.zoom(zoom);
	}
	
	COMPONENT_TYPE CameraComponent::GetType() const
	{
		return COMPONENT_TYPE::CAMERA;
	}
}