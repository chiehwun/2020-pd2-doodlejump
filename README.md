# 2020-pd2-DoodleJump

## Video link
####[PD2 Doodle Jump Project Demo](https://youtu.be/aSYiyHHYCv8)
## How to play
##### 1. Press Enter to Play Again
##### 2. Press Space to shoot
##### 3. Equip propellers and jetpacks to speedup
##### 3. Avoid Mosters and Hazards
## Requirements
 - Player can jump automatically and can move across the boundary (10%)
 - At least two kinds of platforms (10%)
 - At least two kinds of game props (10%)
 - Hazards
     - Monster (5%)
     - Player can shoot bullets to blast the monster (5%)
     - If the monster is dead, remove it from the scene (5%)
     - At least one another hazard (5%)
     - Eliminate/Avoid one hazard someway (5%)
 - Can play the game infinitely until the player died (10%)
 - Can pause the game (5%)
 - Show the player's score during the game (5%)
 - Show GAME OVER and final score when the player died (5%)
 - Platforms’ classes should use polymorphism (10%)
 - README file (10%)

## Polymorphism
``` C++
if(Prop *pp = dynamic_cast<Prop *>(col_items.at(i))) {
    setTransform(Lpos);
    setImg(":/img/player_left0", true);
    pp->touch();        // Polymorphism HERE!!
```
####  說明
##### Class Define: Jetpack 繼承於 Prop
``` C++
class Jetpack: public Prop
```
##### 在 Prop 中定義 touch() 為 virtual
``` C++
virtual void touch();
```
程式在此需要透過 pointer 呼叫 Jetpack::touch() 或 Prop::touch()
會自動依據 Class 呼叫各自的 touch()


## Bonus
1. 血汗地刻出許多動畫效果
   - 螺旋槳旋轉
   - 噴射背噴火
   - 人物加速度移動效果
   - 木質踏板碎掉效果
   - 發射子彈人物圖像變化效果
   - 玩家踩掉怪物
2. 玩家可以踩掉怪物
3. 玩家在加速過程中，不會因碰觸 Hazard 而結束遊戲

## Notes
#### 此遊戲使用Qt開發，其版本資訊如下：
![Imgur](https://i.imgur.com/4877JmO.png)
#### 若遇到無法開啟問題，請聯絡以下Email:
#### e14066282@gs.ncku.edu.tw
