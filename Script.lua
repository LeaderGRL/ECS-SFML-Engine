local EManager = EntityManager:GetInstance()
local player = EManager:GetEntity("Fighter")
print(player:PrintNumber())
player:SetPosition(0,0)
