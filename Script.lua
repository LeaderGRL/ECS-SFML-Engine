local EManager = EntityManager:GetInstance()
EManager:CreateEntity("Player")
local player = EManager:GetEntity("Player")
local fighter = Sprite2DComponent()
local RManager = ResourceManager:GetInstance()
fighter:SetSprite(RManager:GetTexture("Fighter"))
player:AddComponent(fighter)
--player:GetComponent
