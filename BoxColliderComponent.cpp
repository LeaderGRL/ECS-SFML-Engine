#include "pch.h"
#include "BoxColliderComponent.h"

namespace LeaderEngine
{
	BoxColliderComponent::BoxColliderComponent(sf::Vector2f size)
	{
		this->size = size;
	}

	BoxColliderComponent::~BoxColliderComponent()
	{
	}

	void BoxColliderComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//states.transform.combine();
		sf::RectangleShape rect;
		rect.setSize(size);
		rect.setOrigin(size.x / 2, size.y / 2);
		rect.setPosition();
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(1);
		target.draw(rect);
	}

	/*sf::Vector2f BoxColliderComponent::getSize()
	{
		return size;
	}

	void BoxColliderComponent::setSize(sf::Vector2f size)
	{
		this->size = size;
	}*/

	//void BoxColliderComponent::Start()
	//{
	//}

	//void BoxColliderComponent::Update(float deltaTime)
	//{
	//}


	//void BoxColliderComponent::OnCollisionEnter(ColliderComponent* other)
	//{
	//}

	//void BoxColliderComponent::OnCollisionStay(ColliderComponent* other)
	//{
	//}

	//void BoxColliderComponent::OnCollisionExit(ColliderComponent* other)
	//{
	//}
}