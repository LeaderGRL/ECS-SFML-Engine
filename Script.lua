local EManager = EntityManager:GetInstance()
EManager:CreateEntity("Player")
local player = EManager:GetEntity("Player")
local fighter = Sprite2DComponent()
print(ResourceManager:GetInstance())
fighter:SetSprite(ResourceManager:GetInstance():GetTexture("Fighter"))
player:AddComponent(fighter)
--player:GetComponent
