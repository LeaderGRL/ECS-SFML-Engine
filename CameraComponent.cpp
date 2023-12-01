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
		return _view;
	}
	
	void CameraComponent::setView(const sf::View& view)
	{
		this->_view = view;
	}
	
	sf::Vector2f CameraComponent::getPosition()
	{
		return _position;
	}
	
	void CameraComponent::setPosition(sf::Vector2f position)
	{
		this->_position = position;
	}
	
	sf::Vector2f CameraComponent::getSize()
	{
		return _size;
	}
	
	void CameraComponent::setSize(const sf::Vector2f& size)
	{
		this->_size = size;
	}
	
	float CameraComponent::getRotation()
	{
		return _rotation;
	}
	
	void CameraComponent::setRotation(float rotation)
	{
		this->_rotation = rotation;
	}
	
	float CameraComponent::getZoom()
	{
		return _zoom;
	}
	
	void CameraComponent::setZoom(float zoom)
	{
		this->_zoom = zoom;
	}
	
	void CameraComponent::Update(float deltaTime)
	{
		_view.setCenter(_position);
		_view.setRotation(_rotation);
		_view.setSize(_size);
		_view.zoom(_zoom);
		std::cout << _rotation << std::endl;
		std::cout << _view.getRotation() << std::endl;
	}
	
	COMPONENT_TYPE CameraComponent::GetType() const
	{
		return COMPONENT_TYPE::CAMERA;
	}
}