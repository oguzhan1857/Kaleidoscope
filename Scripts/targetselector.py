kaleidoscope  = __import__("kaleidoscope")

import ui
from damage import Damage

class TargetMode:
    @staticmethod
    def get_target_by_weight(source, enemyList):
        target  = None
        damage  = 10000.0
        for next_target in enemyList:
            next_target_damage = next_target.GetHealth() / Damage.calculate_auto_attack_damage(source, next_target)
            if next_target_damage < damage:
                damage = next_target_damage
                target = next_target
        return target

class TargetSelector(ui.Menu):
    def __init__(self, title):
        ui.Menu.__init__(self, title)
        self.init_instances()
        self.build()

    def init_instances(self):
        self.player       = kaleidoscope.GetPlayer()
        self.cursor       = kaleidoscope.HudManager.GetInstance().GetWorldCursor()
        self.target       = None
        self.force_target = None

    def build(self):
        self.draw_target_checkbox         = ui.Checkbox.create(self, "Draw Target", True)
        self.enable_force_target_checkbox = ui.Checkbox.create(self, "Force Target", True)

    def OnDoubleClick(self):
        cursor_target = None
        cursor_pos    = self.cursor.GetPos()
        enemy_list    = kaleidoscope.GetEnemyHeroes()
        distance      = 10000.0
        for enemy in enemy_list:
            current_distance = cursor_pos.DistanceTo(enemy.GetPos())
            if current_distance < 200.0 and current_distance < distance:
                distance = current_distance
                cursor_target = enemy
        
        if cursor_target != None:
            self.force_target = cursor_target
            kaleidoscope.AddLog(f"target changed: {self.force_target}")
        else:
            self.force_target = None

    def get_target(self, range):
        if self.enable_force_target_checkbox.get_value():
            if self.force_target != None:
                if self.player.GetPos().InRange(self.force_target.GetPos(), range) and self.force_target.IsTargetable():
                    return self.force_target
        
        enemyList   = kaleidoscope.GetEnemyHeroes()
        enemyList   = [enemy for enemy in enemyList if self.player.GetPos().InRange(enemy.GetPos(), range) and enemy.IsTargetable()]
        self.target = None
        if(enemyList):
            if(len(enemyList) == 1):
                self.target = enemyList[0]
            else:
                self.target = TargetMode.get_target_by_weight(self.player, enemyList)
                
        return self.target

    def OnRender(self):
        if(self.draw_target_checkbox.get_value()):
            if(self.target and self.player.IsAlive()):
                color  = kaleidoscope.Vector4(0.82, 0, 0.01, 1.00)
                kaleidoscope.DrawCircle3D(self.target.GetPos(), self.target.GetBound(), color, 1.3)

        if self.enable_force_target_checkbox.get_value():
            if self.force_target and self.player.IsAlive():
                color  = kaleidoscope.Vector4(0.094, 0.976, 0.062, 1.00)
                kaleidoscope.DrawCircle3D(self.force_target.GetPos(), self.force_target.GetBound() + 30.0, color, 1.3)