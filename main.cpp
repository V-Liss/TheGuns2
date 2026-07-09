#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace sf;

int projectile_count=100;

//int types=1;
int y_boss=false;
int x_boss=false;
int wasHealth;
int types_count=2;
int drop_count=1000;
int idle=0;
int prefire=1;
int fire=2;
int reload=3;
int deploy=4;

int engage=1;
int aim=2;
int backpedal=3;

int friction=1;
int map_now=0;
int level_unlocked=0;
double PI=3.141592653589793;
int wheel=0;
int game=2;
int main_menu=0;
int game_state=0;
int workshop=1;
int pause=3;
bool wasF11Pressed=false;
bool isF11Released=false;
bool isFullScreen=false;
bool wasPressed=false;
bool isReleased=false;
int levels_count=6;
int map_count=1;
//bool isStage2Unlocked=false;
//
//int guns_count=1;
int items_count=13;
int blueprint_count=5;
int bluepr=0;
int gravity=3;
//

double prc(double a, double b)
{
    while (a<0)
    {
        a+=b;
    }
    for (double i=a-b; i>0; i=a-b)
    {
        a-=b;
    }
    return a;
}

double rotation (double x, double y)
{
    if (x>0&&y>=0)
    {
        return atan(y/x);
    }
    if (x<0&&y>=0)
    {
        return atan (y/x) + PI;
    }
    if (x<0&&y<0)
    {
        return atan (y/x) + PI;
    }
    if (x>0&&y<0)
    {
        return atan (y/x);
    }
    if (x==0)
    {
        if (y>0)
            return (PI/2);
        else
            return (3*PI/2);
    }
}

int sign(float a)
{
    if (a>0)
        return 1;
    else if (a<0)
        return -1;
    else return 0;
}

int round1(double a)
{
    if (a-int(a)>=0.5)
    {
        return int(a)+1;
    }
    else
        return int(a);
}

class vec
{
public:
    double x=0;
    double y=0;
    vec(double newx, double newy)
    {
        x=newx;
        y=newy;
    }
    vec()
    {
        x=0;
        y=0;
    }
    void setXY(int newx, int newy)
    {
        x=newx;
        y=newy;
    }
    vec operator+(vec v)
    {
        v.x+=x;
        v.y+=y;
        return v;
    }
    vec operator-(vec v)
    {
        v.x-=x;
        v.y-=y;
        return v;
    }
    void operator+=(vec v)
    {
        x+=v.x;
        y+=v.y;
        return;
    }
    void operator-=(vec v)
    {
        x-=v.x;
        y-=v.y;
        return;
    }
    void operator=(vec v)
    {
        x=v.x;
        y=v.y;
        return;
    }
    bool operator==(vec v)
    {
        if (x==v.x&&y==v.y)
        {
            return true;
        }
        else
            return false;
    }
};

class Map
{
public:
    vec pos;
    vec speed;
    int width=0;
    int height=0;
    int twidth=0;
    int theight=0;
    Texture back_texture;
    Sprite back_sprite;
    Texture** texture;
    Sprite** sprite;
    int** M;
    Map()
    {
        width=0;
        height=0;
        twidth=0;
        theight=0;
    }
    Map(int w, int h, std::string path)
    {
        M=new int*[w];
        for (int i=0; i<w; i++)
        {
            M[i]=new int[h];
        }
        for (int i=0; i<w; i++)
        {
            for (int j=0; j<h; j++)
            {
                M[i][j]=0;
            }
        }
        for (int i=0; i<w; i++)
        {
            M[i][0]=1;
            M[i][h-1]=1;
        }
        for (int i=0; i<w; i++)
        {
            M[0][i]=1;
            M[w-1][i]=1;
        }
        width=w;
        height=h;

        if (width%1920==0)
        {
            twidth=width/1920+1;
        }
        else
        {
            twidth=width/1920+2;
        }

        if (height%1080==0)
        {
            theight=height/1080+1;
        }
        else
        {
            theight=height/1080+2;
        }

        texture=new Texture*[twidth];
        sprite=new Sprite*[twidth];
        for (int i=0; i<twidth; i++)
        {
            texture[i]=new Texture[theight];
            sprite[i]=new Sprite[theight];
            for (int j=0; j<theight; j++)
            {
                std::string str="";
                str+=path;
                str+=std::to_string(i);
                str+="-";
                str+=std::to_string(j);
                str+=".png";
                texture[i][j].loadFromFile(str);
                sprite[i][j].setTexture(texture[i][j]);
                sprite[i][j].setTextureRect(IntRect(0, 0, 1920, 1080));
            }
        }
    }
    void create(int w, int h, std::string path, std::string back_path)
    {
        M=new int*[w];
        for (int i=0; i<w; i++)
        {
            M[i]=new int[h];
        }
        for (int i=0; i<w; i++)
        {
            for (int j=0; j<h; j++)
            {
                M[i][j]=0;
            }
        }
        for (int i=0; i<w; i++)
        {
            M[i][0]=1;
            M[i][h-1]=1;
        }
        for (int i=0; i<h; i++)
        {
            M[0][i]=1;
            M[w-1][i]=1;
        }
        width=w;
        height=h;

        if (width%1920==0)
        {
            twidth=width/1920+1;
        }
        else
        {
            twidth=width/1920+2;
        }

        if (height%1080==0)
        {
            theight=height/1080+1;
        }
        else
        {
            theight=height/1080+2;
        }

        texture=new Texture*[twidth];
        sprite=new Sprite*[twidth];
        for (int i=0; i<twidth; i++)
        {
            texture[i]=new Texture[theight];
            sprite[i]=new Sprite[theight];
            for (int j=0; j<theight; j++)
            {
                std::string str="";
                str+=path;
                str+=std::to_string(i);
                str+="-";
                str+=std::to_string(j);
                str+=".png";
                texture[i][j].loadFromFile(str);
                sprite[i][j].setTexture(texture[i][j]);
                sprite[i][j].setTextureRect(IntRect(0, 0, 1920, 1080));
            }
        }
        back_texture.loadFromFile(back_path);
        back_sprite.setTexture(back_texture);

        return;
    }
};




class Position
{
public:
    vec pos;
    vec speed;
    void punch(vec newspeed)
    {
        speed+=newspeed;
        return;
    }

    void engine(int head_height, int height, int width, Map mp)
    {
    //speed.y+=gravity;
    bool bumped_x=false;
    bool bumped_y=false;
    double a1=speed.x;
    double b1=speed.y;
    double cosinus=cos(rotation(speed.x, speed.y));
    double sinus=sin(rotation(speed.x, speed.y));

        //std::cout << std::endl;

        while ((sign(speed.x)==sign(a1)&&speed.x!=0)||(sign(speed.y)==sign(b1)&&speed.y!=0))
        {
            //std::cout << position.x << " " << cosinus << std::endl;
            //std::cout << position.speed_x << std::endl;
            //std::cout << position.y << std::endl;
            //std::cout << position.speed_y << std::endl << std::endl;

            for (int i=-head_height; i<=height; i++)
            {
                if (mp.M[round1(pos.x)+(width+1)*sign(speed.x)][round1(pos.y)+i]>0)
                {
                    bumped_x=true;
                    speed.x=0;
                }
            }
            if (sign(speed.x)==sign(a1)&&speed.x!=0)
            {
                if (abs(speed.x)>abs(cosinus))
                {
                    pos.x+=cosinus;
                    speed.x-=cosinus;
                }
                else
                {
                    pos.x+=speed.x;
                    speed.x=0;
                }

            }
            for (int i=-width; i<=width; i++)
            {
                if (speed.y>0&&mp.M[round1(pos.x)+i][round1(pos.y)+height+1]>0)
                {
                    bumped_y=true;
                    speed.y=0;
                }
                else if (speed.y<0&&mp.M[round1(pos.x)+i][round1(pos.y)-head_height-1]>0)
                {
                    bumped_y=true;
                    speed.y=0;
                }
            }
            if (sign(speed.y)==sign(b1)&&speed.y!=0)
            {
                if (abs(speed.y)>abs(sinus))
                {
                    pos.y+=sinus;
                    speed.y-=sinus;
                }
                else
                {
                    pos.y+=speed.y;
                    speed.y=0;
                }

            }
        }
        if (!bumped_x)
            speed.x=a1;
        else
            speed.x=0;
        if (!bumped_y)
            speed.y=b1;
        else
            speed.y=0;
        return;
    }
};


class Animation
{
public:
    //int scale=1;
    double step_length=1;
    double pos=0.1;
    int length=0;
    Texture* texture;
    int height=0;
    int width=0;
    int shift_x=0;
    int shift_y=0;
    Sprite sprite;
    double shift_rotation;
    double shift;
    double* frame_pos;
    Animation()
    {

    }
    void create(int l, int w, int h, int sh_x, int sh_y, double newstep)
    {
        width=w;
        height=h;
        texture=new Texture[l];
        length=l;
        sprite.setTexture(texture[0]);
        sprite.setTextureRect(IntRect(0, 0, width,  height));
        shift_x=sh_x;
        shift_y=sh_y;
        shift=sqrt(shift_x*shift_x+shift_y*shift_y);
        shift_rotation=rotation(-shift_x, shift_y);
        step_length=newstep;
        //std::cout << shift_rotation/PI;
        return;
    }
    void step(double l)
    {
        pos+=l;
        pos=prc(pos, length);
        int temp=int(pos);
        if (temp<length)
        {
            sprite.setTexture(texture[temp]);
        }
        else
        {
            sprite.setTexture(texture[0]);
        }

        sprite.setTextureRect(IntRect(0, 0, width, height));
        return;
    }
    void step1()
    {
        pos+=step_length;
        pos=prc(pos, length);
        int temp=int(pos);
        if (temp<length)
        {
            sprite.setTexture(texture[temp]);
        }
        else
        {
            sprite.setTexture(texture[0]);
        }

        sprite.setTextureRect(IntRect(0, 0, width, height));
        return;
    }
    void setPos(double newpos)
    {
        pos=newpos;
        pos=prc(pos, length);
        int temp=int(pos);
        if (temp<length)
        {
            sprite.setTexture(texture[temp]);
        }
        else
        {
            sprite.setTexture(texture[0]);
        }

        sprite.setTextureRect(IntRect(0, 0, width, height));
        return;
    }
    void setFrame(int frame)
    {
        setPos(frame_pos[frame]);
    }
    void fill_frames(std::string str, int frames)
    {
        for (int i=0; i<length; i++)
        {
            int j=i/frames;
            std::string str1=str;
            str1+=std::to_string(j);
            str1+=".png";
            texture[i].loadFromFile(str1);
        }
        sprite.setTexture(texture[0]);
        return;
    }
    void setPR(int scale, int x, int y, double rotation)
    {
        sprite.setRotation(rotation*57);
        double rot=scale*shift_rotation-rotation;
        //std::cout << rot/PI << std::endl;

            sprite.setPosition(x+shift*cos(rot)*scale, y-shift*sin(rot)*scale);

            //sprite.setPosition(x-shift*cos(rot), y+shift*sin(rot));


        sprite.setScale(scale, 1);
        return;
    }
};
class Button
{
public:

    Texture texture1;
    Texture texture2;
    Sprite sprite;
    vec pos;
    int width;
    int height;
    bool isUnlocked=false;
    Button()
    {
        width=0;
        height=0;
    }
    Button(std::string string1, std::string string2, int x, int y, int w, int h)
    {
        texture1.loadFromFile(string1);
        texture2.loadFromFile(string2);
        sprite.setTexture(texture1);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        width=w;
        height=h;
        sprite.setPosition(x, y);
        pos.setXY(x, y);
    }
    void create(std::string string1, std::string string2, int x, int y, int w, int h)
    {
        texture1.loadFromFile(string1);
        texture2.loadFromFile(string2);
        sprite.setTexture(texture1);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        width=w;
        height=h;
        sprite.setPosition(x, y);
        pos.setXY(x, y);
    }
    void setPosition(int x, int y)
    {
        pos.setXY(x, y);
        sprite.setPosition(x, y);
    }
    void expand()
    {
        sprite.setTexture(texture2);
        sprite.setScale(double(width+20)/width, double(height+20)/height);
        sprite.setPosition(pos.x-10, pos.y-10);
        return;
    }
    void shrink()
    {
        sprite.setTexture(texture1);
        sprite.setScale(1, 1);
        sprite.setPosition(pos.x, pos.y);
        return;
    }
    bool isPointed(Vector2i mousepos)
    {
        if (IntRect(pos.x, pos.y, width, height).contains(mousepos))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Slot
{
public:
    //bool isWeapon=false;
    bool full=false;
    int holding=0;
    Texture texture;
    Sprite sprite;
    Button button;
    void equip(bool w, bool f, int h)
    {
        //isWeapon=w;
        full=f;
        holding=h;
    }
};


class Gun
{
public:
    int predelay=0;
    int max_predelay=0;
    //int state=0;
    int knockback=5;
    int self_knockback=0;
    //String name;
    //String temp="";
    Animation left;
    Animation right;
    Animation left_pre;
    Animation right_pre;
    Animation left_reload;
    Animation right_reload;
    Animation left_deploy;
    Animation right_deploy;
    Animation pre;
    Animation blast;
    Animation projectile;
    SoundBuffer exp_buffer;
    Texture bullet_texture;
    Sprite bullet;
    //Texture icon_texture;
    //Sprite icon;
    Animation crosshair;
    Animation animation;
    SoundBuffer buffer;
    Sound sound;
    Animation deploy;
    Animation reload;
    int width=100;
    int height=100;
    int max_delay=20;
    int damage=25;
    int delay=0;
    bool isPistol=true;
    int max_distance=1200;
    double spread=0;
    int pellets=0;
    double pellet_spread=0.05;
    double swiftness=1;
    bool isProjectile=true;
    int radius=10;
    int proj_speed=300;
    int max_projectile_time=5;
    int proj_width=10;
    int proj_length=100;
    int proj_acceleration=0;
    double splash_multiplier=2;
    int max_deploy=10;
    int deploy_counter=0;


    int max_ammo=12;
    int ammo=0;
    int ammo_used=1;
    int item_ammo=0;
    int max_reload=45;
    int reload_counter=0;
/*
    double* pos_delay;
    double* pos_predelay;
    double* pos_reload;
    double* pos_deploy;*/
    void create(int newmax_predelay, int newmax_delay, int newmax_deploy, int newmax_reload)
    {
        max_delay=newmax_delay;
        max_deploy=newmax_deploy;
        max_predelay=newmax_predelay;
        max_reload=newmax_reload;
        animation.frame_pos=new double[max_delay+1];
        pre.frame_pos=new double[max_predelay+1];
        reload.frame_pos=new double[max_reload+1];
        deploy.frame_pos=new double[max_deploy+1];
        left.frame_pos=new double[max_delay+1];
        left_pre.frame_pos=new double[max_predelay+1];
        left_reload.frame_pos=new double[max_reload+1];
        left_deploy.frame_pos=new double[max_deploy+1];
        right.frame_pos=new double[max_delay+1];
        right_pre.frame_pos=new double[max_predelay+1];
        right_reload.frame_pos=new double[max_reload+1];
        right_deploy.frame_pos=new double[max_deploy+1];
    }
};

/*struct Hand
{
    Animation left;
    Animation right;
};*/

class Item
{
public:
    Font font;
    double swiftness=1;
    int quantity=0;
    bool isWeapon=false;
    bool isStackable=true;
    std::string name="";
    vec pos;
    Button button;
    int width=0;
    int height=0;
    Gun gun;
    Text text;
    Text stats;
    Text ammo;
    std::string ammo_str="";

    Item()
    {
        font.loadFromFile("Textures/utility/font.ttf");
        text.setFont(font);
        text.setCharacterSize(20);
        text.setStyle(Text::Regular);
        text.setColor(Color(0, 0, 255));
        stats.setFont(font);
        stats.setCharacterSize(30);
        stats.setStyle(Text::Regular);
        stats.setColor(Color(0, 127, 0));
        ammo.setFont(font);
        ammo.setCharacterSize(30);
        ammo.setStyle(Text::Regular);
        ammo.setColor(Color(0, 127, 0));
        //stats.setPosition(50, 1000);
    }
    void create(std::string n, std::string path1, int x, int y, int w, int h)
    {
        name=n;
        button.create(path1, path1, x, y, w, h);
        text.setPosition(x, y+80);

    }
    void setGun(std::string path, int frames_count, int frames, int w, int h, int max_ammo, int item_ammo, double newstep)
    {
        gun.animation.create(frames_count, w, h, w/2, h/2, newstep);
        gun.animation.fill_frames(path, frames);
        isWeapon=true;
        gun.max_ammo=max_ammo;
        gun.item_ammo=item_ammo;
    }
    void setPosition(int x, int y)
    {
        button.setPosition(x, y);
        text.setPosition(x, y+80);
    }
    void setText()
    {
        std::string count_str="x";
        count_str+=std::to_string(quantity);
        text.setString(count_str);
    }
};



class Blueprint
{
public:
    int* number;
    int* quantity;
    int item_crafted;
    int ctr;
    int crafted_count=1;
    bool isOpen=false;
    Texture texture;
    Sprite sprite;
    Blueprint()
    {

    }
    void create(int q, std::string path)
    {
        number=new int[q];
        quantity=new int[q];
        ctr=q;
        texture.loadFromFile(path);
        sprite.setTexture(texture);
    }

};


class Drop
{
public:
    Position position;
    int number=0;
    Sprite sprite;
    bool is=false;
};


class Entity
{
public:
    bool isBeaten=false;
    int counter=0;
    vec* spawn=new vec[map_count];
    bool* isSpawned=new bool[map_count];
    int quantity=0;
    int death_counter=0;
    bool isStanding;
    bool wasDead=true;
    Texture idle;
    Texture jump;
    //Hand* hands=new Hand[items_count];
    Slot* slot=new Slot[4];
    Animation body;
    Animation head;
    Animation death;
    Texture bullet_texture;
    Sprite bullet;
    //Hand *hands = new Hand[guns_count];
    Position position;
    int health=120;
    int max_health=120;
    int slot_holding=0;
    //int body_frame_counter=0;
    int pos_x=10;
    int pos_y=0;
    int jump_force=60;
    int head_height=41;
    int height=97;
    double tilt=0;
    double tilt_speed=-1;
    int air_strafe_force=1;
    int strafe_force=2;
    int delay=30;
    int max_delay=30;
    int guns_delay=10;
    int max_guns_delay=15;
    int sight_x=1200;
    int sight_y=960;
    int max_speed=20;
    int animation_delay=0;
    SoundBuffer weapon_buffer;
    Sound weapon_sound;
    int shots_left=3;
    int max_shots=3;
    int width=20;
    int max_tilt=10;
    //int shield=0;
    //int max_shield=60;
    int phase=0;
    bool play=false;
    int deploy=0;
    int canEquip()
    {
        for (int i=0; i<4; i++)
        {
            if (!slot[i].full)
            {
                return i;
            }
        }
        return -1;
    }
    void unequip (int s)
    {
        slot[s].full=false;
    }
    void equip(int n)
    {
        int i=canEquip();
        if (i>-1)
        {
            slot[i].full=true;
            slot[i].holding=n;
        }
    }
};

class Projectile
{
public:
    int knockback=0;
    double x=0;
    double y=0;
    int damage=0;
    int speed=0;
    double rotation=0;
    int radius=0;
    int distance_left=0;
    int time=0;
    int acceleration=0;
    Animation animation;
    Sound explosion;
    Animation blast;
    int gun=0;
    double multiplier=1;
};


struct Bullet
{
    int damage=0;
    double final_x=0;
    double final_y=0;
    bool hit=false;
    int distance=0;
};

double rt(double x, double y)
{
    if (x!=0)
    {
        return atan(y/x);
    }
    else if (y>=0)
    {
        return 90.0/57;
    }
    else
    {
        return -90.0/57;
    }
}





double random(double max1)
{

    if (max1>0)
        return ((prc(double(rand()), max1))-max1/2);
    else
        return 0;
}



int sign1(float a)
{
    if (a>=0)
        return 1;
    else
        return -1;
}

Bullet shoot (double ent_x, double ent_y, int head_height, int height, int width, double angle, double x, double y, int damage, int max_distance, Map mp)
{
    Bullet bullet;
    double sinus=sin(angle);
    double cosinus=cos(angle);

    for (; bullet.distance<max_distance&&mp.M[round1(x)][round1(y)]==0; bullet.distance++)
    {
        if (x>=ent_x-width&&x<=ent_x+width)
        {

            if (y>=ent_y&&y<=ent_y+height)
            {
                bullet.hit=true;
                bullet.damage=damage;
                bullet.final_x=x;
                bullet.final_y=y;
                return bullet;
            }
            else if (y>=ent_y-head_height&&y<=ent_y)
            {
                bullet.hit=true;
                bullet.damage=damage*2;
                bullet.final_x=x;
                bullet.final_y=y;
                return bullet;
            }
        }
        x+=cosinus;
        y+=sinus;
    }
    bullet.final_x=x;
    bullet.final_y=y;
    return bullet;

}

Bullet enemy_shoot (double ent_x, double ent_y, int head_height, int height, int width, double angle, double x, double y, int damage, int max_distance, Map mp)
{
    Bullet bullet;
    double sinus=sin(angle);
    double cosinus=cos(angle);

    for (; bullet.distance<max_distance&&mp.M[round1(x)][round1(y)]==0; bullet.distance++)
    {
        if (x>=ent_x-width&&x<=ent_x+width)
        {
            if (y>=ent_y-head_height&&y<=ent_y)
            {
                bullet.hit=true;
                bullet.damage=damage*2;
                bullet.final_x=x;
                bullet.final_y=y;
                return bullet;
            }
            if (y>=ent_y&&y<=ent_y+height)
            {
                bullet.hit=true;
                bullet.damage=damage;
                bullet.final_x=x;
                bullet.final_y=y;
                return bullet;
            }
        }
        x+=cosinus;
        y+=sinus;
    }
    bullet.final_x=x;
    bullet.final_y=y;
    return bullet;
}


bool canShoot (double x1, double y1, double x2, double y2, int** M)
{
    double sinus=sin(rotation(x2-x1, y2-y1));
    double cosinus=cos(rotation(x2-x1, y2-y1));
    int sign2=sign(x2-x1);
    while (sign2==sign(x2-x1))
    {
        if (M[round1(x1)][round1(y1)])
        {
            return false;
        }
        x1+=cosinus;
        y1+=sinus;
    }
    return true;
}
//mp.M
int damage(double multiplier, double enemy_x, double enemy_y, int width, double enemy_y1, double enemy_y2, double projectile_x, double projectile_y, double radius, int dmg, int** M)
{
    int dmg1=0;
    for (double i=enemy_y1; i<enemy_y; i++)
    {
        for (double j=enemy_x-width; j<=enemy_x+width; j++)
        {
            int dmg2=round1((radius-sqrt((j-projectile_x)*(j-projectile_x)+(i-projectile_y)*(i-projectile_y)))*dmg/radius)*multiplier;
            if (dmg1<dmg2&&canShoot(projectile_x, projectile_y, j, i, M))
            {
                dmg1=dmg2;
            }
        }


    }

    for (double i=enemy_y; i<=enemy_y2; i++)
    {
        for (double j=enemy_x-width; j<=enemy_x+width; j++)
        {
            int dmg2=round1((radius-sqrt((j-projectile_x)*(j-projectile_x)+(i-projectile_y)*(i-projectile_y)))*dmg/radius);
            if (dmg1<dmg2&&canShoot(projectile_x, projectile_y, j, i, M))
            {
                dmg1=dmg2;
            }
        }


    }
    return dmg1;
}

int main()
{
    Animation rocket;
    Animation explosion;

    rocket.create(1, 100, 15, 100, 7, 0.1);
    rocket.fill_frames("Textures/enemies/1/rocket", 1);
    explosion.create(3, 400, 400, 200, 200, 0.2);
    explosion.fill_frames("Textures/enemies/1/explosion", 1);


    srand(time(NULL));
    std::cout << "Loading The Guns 2...";
    //
    Map* mp=new Map[map_count];
    mp[0].create(11520, 1080, "Textures/maps/0/", "Textures/maps/0/back.png");
    mp[0].pos.setXY(1000, 900);
    for (int i=1730; i<1980; i++)
    {
        for (int j=760; j<1080; j++)
        {
            mp[0].M[i][j]=1;
        }
    }
    for (int i=4605; i<4641; i++)
    {
        for (int j=801; j<1080; j++)
        {
            mp[0].M[i][j]=1;
        }
    }
    for (int i=5131; i<5174; i++)
    {
        for (int j=801; j<890; j++)
        {
            mp[0].M[i][j]=1;
        }
    }
    for (int i=4578; i<5206; i++)
    {
        for (int j=786; j<800; j++)
        {
            mp[0].M[i][j]=1;
        }
    }
    for (int i=4642; i<4790; i++)
    {
        mp[0].M[i][935]=1;
    }
    for (int i=9113; i<9172; i++)
    {
        for (int j=0; j<540; j++)
        {
            mp[0].M[i][j]=1;
        }
    }

    for (int i=9113; i<9172; i++)
    {
        for (int j=793; j<1080; j++)
        {
            mp[0].M[i][j]=1;
        }
    }
    for (int i=9172; i<9634; i++)
    {
        mp[0].M[i][793]=1;
    }
    for (int i=9762; i<10232; i++)
    {
        mp[0].M[i][543]=1;
    }

    for (int i=10903; i<11374; i++)
    {
        mp[0].M[i][793]=1;
    }

    for (int i=11374; i<11432; i++)
    {
        for (int j=0; j<798; j++)
        {
            mp[0].M[i][j]=1;
        }
    }
    /*for (int i=1500; i<2000; i++)
    {
        for (int j=-920+i; j<1080; j++)
        {
            mp[0].M[i][j]=1;
        }
    }*/

    //mp[0].speed.setXY(20, -40);
    Projectile* projectile=new Projectile[projectile_count];
    Projectile* enemy_projectile=new Projectile[projectile_count];

    for (int i=1; i<100; i++)
    {
        for (int j=1; j<1079; j++)
        mp[0].M[i][j]=-1;
    }
    for (int i=11500; i<11520; i++)
    {
        for (int j=1; j<1079; j++)
        {
            mp[0].M[i][j]=-1;
        }
    }

    Drop* drop=new Drop[drop_count];


    View view;
    View stockview;
    stockview.setSize(1920, 1080);
    stockview.setCenter(960.0, 540.0);
    Font font;
    Text text;
    font.loadFromFile("Textures/utility/font.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setColor(Color::Red);
    Entity player;
    Entity** enemy = new Entity*[types_count];
    Texture empt;
    empt.loadFromFile("Textures/utility/empty.png");
    player.body.create(6, 100, 100, 50, 0, 1);
    player.body.fill_frames("Textures/player/", 1);
    player.body.setPR(1, 960, 540, 0);
    player.head.create(2, 50, 50, 25, 50, 0.05);
    player.head.setPR(1, 960, 540, 0);
    player.head.fill_frames("Textures/player/head", 1);
    player.idle.loadFromFile("Textures/player/idle.png");
    player.jump.loadFromFile("Textures/player/jump.png");

    enemy[0]=new Entity[10];
    enemy[1]=new Entity[1];
    enemy[1][0].quantity=1;
//enemy[1][0].quantity
    for (int i=0; i<10; i++)
    {
        enemy[0][i].death.create(3, 120, 120, 60, 20, 0.1);
        enemy[0][i].death.fill_frames("Textures/enemies/0/death", 1);
        enemy[0][i].death.frame_pos=new double[31];
        for (int j=0; j<10; j++)
        {
            enemy[0][i].death.frame_pos[j]=2.1;
        }
        for (int j=10; j<20; j++)
        {
            enemy[0][i].death.frame_pos[j]=1.1;
        }
        for (int j=20; j<31; j++)
        {
            enemy[0][i].death.frame_pos[j]=0.1;
        }
        enemy[0][i].body.create(2, 80, 80, 40, 0, 0.15);
        enemy[0][i].idle.loadFromFile("Textures/enemies/0/1.png");
        enemy[0][i].body.fill_frames("Textures/enemies/0/", 1);
        enemy[0][i].head.create(2, 80, 80, 40, 80, 0.1);
        enemy[0][i].head.fill_frames("Textures/enemies/0/head", 1);
        enemy[0][i].head_height=25;
        enemy[0][i].height=77;
        enemy[0][i].max_speed=5;
        enemy[0][i].max_health=45;
        enemy[0][i].strafe_force=2;
        for (int j=0; j<map_count; j++)
        {
            enemy[0][i].isSpawned[j]=false;
        }
    }
    enemy[0][0].isSpawned[0]=true;
    enemy[0][0].spawn[0].setXY(2000, 900);
    enemy[0][0].quantity=10;

    enemy[0][1].isSpawned[0]=true;
    enemy[0][1].spawn[0].setXY(4705, 1000);

    enemy[0][2].isSpawned[0]=true;
    enemy[0][2].spawn[0].setXY(4705, 840);

        enemy[1][0].death.create(6, 300, 200, 150, 0, 0.1);
        enemy[1][0].death.fill_frames("Textures/enemies/1/death", 1);
        enemy[1][0].death.frame_pos=new double[161];

        for (int j=0; j<60; j++)
        {
            enemy[1][0].death.frame_pos[j]=5.1;
        }
        for (int j=60; j<80; j++)
        {
            enemy[1][0].death.frame_pos[j]=4.1;
        }
        for (int j=80; j<100; j++)
        {
            enemy[1][0].death.frame_pos[j]=3.1;
        }
        for (int j=100; j<120; j++)
        {
            enemy[1][0].death.frame_pos[j]=2.1;
        }
        for (int j=120; j<140; j++)
        {
            enemy[1][0].death.frame_pos[j]=1.1;
        }
        for (int j=140; j<161; j++)
        {
            enemy[1][0].death.frame_pos[j]=0.1;
        }

        enemy[1][0].body.create(1, 300, 200, 150, 0, 0.15);

        enemy[1][0].body.fill_frames("Textures/enemies/1/body", 1);

        enemy[1][0].idle.loadFromFile("Textures/enemies/1/body0.png");
        //enemy[1][0].body.fill_frames("Textures/enemies/0/", 1);
        enemy[1][0].head.create(3, 400, 200, 200, 100, 0.2);
        enemy[1][0].head.fill_frames("Textures/enemies/1/head", 1);
        enemy[1][0].width=150;
        enemy[1][0].head_height=200;
        enemy[1][0].height=197;
        //enemy[1][0].max_speed=5;
        enemy[1][0].max_health=500;
        //enemy[1][0].strafe_force=2;
        for (int j=0; j<map_count; j++)
        {
            enemy[1][0].isSpawned[j]=false;
        }
        enemy[1][0].body.setPos(0.1);
        enemy[1][0].isSpawned[0]=true;
        enemy[1][0].spawn[0].setXY(10232, 882);



    player.slot[0].texture.loadFromFile("Textures/utility/slot.png");
    player.slot[1].texture.loadFromFile("Textures/utility/slot.png");
    player.slot[2].texture.loadFromFile("Textures/utility/slot.png");
    player.slot[3].texture.loadFromFile("Textures/utility/slot.png");


    player.slot[0].sprite.setTexture(player.slot[0].texture);
    player.slot[1].sprite.setTexture(player.slot[1].texture);
    player.slot[2].sprite.setTexture(player.slot[2].texture);
    player.slot[3].sprite.setTexture(player.slot[3].texture);

    player.slot[0].sprite.setPosition(1740, 900);
    player.slot[1].sprite.setPosition(1590, 900);
    player.slot[2].sprite.setPosition(1440, 900);
    player.slot[3].sprite.setPosition(1290, 900);

    player.slot[0].button.create("Textures/utility/empty.png", "Textures/utility/empty.png", 1300, 910, 100, 100);
    player.slot[1].button.create("Textures/utility/empty.png", "Textures/utility/empty.png", 1450, 910, 100, 100);
    player.slot[2].button.create("Textures/utility/empty.png", "Textures/utility/empty.png", 1600, 910, 100, 100);
    player.slot[3].button.create("Textures/utility/empty.png", "Textures/utility/empty.png", 1750, 910, 100, 100);

    /*player.slot[0].button.sprite.setPosition(1750, 910);
    player.slot[1].button.sprite.setPosition(1600, 910);
    player.slot[2].button.sprite.setPosition(1450, 910);
    player.slot[3].button.sprite.setPosition(1300, 910);

    player.slot[0].button.sprite.setTextureRect(IntRect(0, 0, 100, 100));
    player.slot[1].button.sprite.setTextureRect(IntRect(0, 0, 100, 100));
    player.slot[2].button.sprite.setTextureRect(IntRect(0, 0, 100, 100));
    player.slot[3].button.sprite.setTextureRect(IntRect(0, 0, 100, 100));
    */

    Texture boss_bar_texture;
    boss_bar_texture.loadFromFile("Textures/utility/boss_frame.png");
    Sprite boss_bar_sprite;
    boss_bar_sprite.setTexture(boss_bar_texture);
    boss_bar_sprite.setPosition(60, 60);

    Texture boss_h_texture;
    boss_h_texture.loadFromFile("Textures/utility/health.png");
    Sprite boss_h_sprite;
    boss_h_sprite.setTexture(boss_h_texture);
    boss_h_sprite.setPosition(60, 60);




    Texture h_texture;
    h_texture.loadFromFile("Textures/utility/health.png");
    Sprite h_sprite;
    h_sprite.setTexture(h_texture);
    Texture bar_texture;
    bar_texture.loadFromFile("Textures/utility/bar.png");
    Sprite bar_sprite;
    bar_sprite.setTexture(bar_texture);
    h_sprite.setPosition(760, 900);
    bar_sprite.setPosition(760, 900);


//game_state=main_menu


    Blueprint* blueprint=new Blueprint[blueprint_count];
    Item* item=new Item[items_count];

    blueprint[0].create(3, "Textures/blueprints/0.png");
    blueprint[0].number[0]=0;
    blueprint[0].quantity[0]=5;
    blueprint[0].number[1]=1;
    blueprint[0].quantity[1]=1;
    blueprint[0].number[2]=2;
    blueprint[0].quantity[2]=1;
    blueprint[0].item_crafted=3;
    blueprint[0].isOpen=true;

    blueprint[1].create(2, "Textures/blueprints/1.png");
    blueprint[1].number[0]=0;
    blueprint[1].quantity[0]=1;
    blueprint[1].number[1]=5;
    blueprint[1].quantity[1]=1;
    blueprint[1].item_crafted=4;
    blueprint[1].isOpen=true;

    blueprint[2].create(4, "Textures/blueprints/2.png");
    blueprint[2].number[0]=0;
    blueprint[2].quantity[0]=10;
    blueprint[2].number[1]=1;
    blueprint[2].quantity[1]=1;
    blueprint[2].number[2]=2;
    blueprint[2].quantity[2]=1;
    blueprint[2].number[3]=8;
    blueprint[2].quantity[3]=1;
    blueprint[2].item_crafted=6;

    blueprint[3].create(4, "Textures/blueprints/3.png");
    blueprint[3].number[0]=0;
    blueprint[3].quantity[0]=12;
    blueprint[3].number[1]=1;
    blueprint[3].quantity[1]=1;
    blueprint[3].number[2]=2;
    blueprint[3].quantity[2]=1;
    blueprint[3].number[3]=8;
    blueprint[3].quantity[3]=2;
    blueprint[3].item_crafted=11;

    blueprint[4].create(2, "Textures/blueprints/4.png");
    blueprint[4].number[0]=0;
    blueprint[4].quantity[0]=2;
    blueprint[4].number[1]=5;
    blueprint[4].quantity[1]=2;
    blueprint[4].item_crafted=12;


    item[0].create("Scrap Metal", "Textures/items/0/0.png", 100, 100, 100, 100);
    item[1].create("Steel Pipe", "Textures/items/1/0.png", 250, 100, 100, 100);
    item[2].create("Ammo Dispensing Mechanism", "Textures/items/2/0.png", 400, 100, 100, 100);
    item[3].create("Pistol", "Textures/items/3/0.png", 550, 100, 100, 100);
    item[4].create("Small Ammo", "Textures/items/4/0.png", 700, 100, 100, 100);
    item[5].create("Gunpowder", "Textures/items/5/0.png", 850, 100, 100, 100);
    item[6].create("Submachine Gun", "Textures/items/6/0.png", 1000, 100, 100, 100);
    item[7].create("The Wrench", "Textures/items/7/0.png", 100, 250, 100, 100);
    item[8].create("Copper Wires", "Textures/items/8/0.png", 250, 250, 100, 100);
    item[9].create("Rocket", "Textures/items/9/0.png", 400, 250, 100, 100);
    item[10].create("Thick Steel Pipe", "Textures/items/10/0.png", 550, 250, 100, 100);
    item[11].create("Machine Gun", "Textures/items/11/0.png", 700, 250, 100, 100);
    item[12].create("Medium Ammo", "Textures/items/12/0.png", 850, 250, 100, 100);

    /*item[0].quantity=55;
    item[1].quantity=15;
    item[2].quantity=15;
    item[3].quantity=0;*/
    item[3].isStackable=false;

    item[3].setGun("Textures/items/3/gun", 3, 1, 200, 200, 12, 4, 0.1);
    //player.hands[3].left.create(3, 100, 100, 50, 50, 0.1);
    //player.hands[3].left.fill_frames("Textures/items/3/left", 1);

    item[3].gun.pre.create(1, 200, 200, 100, 100, 0.1);
    item[3].gun.left_pre.create(1, 100, 100, 50, 50, 0.1);
    item[3].gun.right_pre.create(1, 100, 100, 50, 50, 0.1);
    item[3].gun.reload.create(2, 200, 200, 100, 100, 0.1);
    item[3].gun.left_reload.create(1, 100, 100, 50, 50, 0.1);
    item[3].gun.right_reload.create(3, 100, 100, 50, 50, 0.1);

    item[3].gun.reload.fill_frames("Textures/items/3/reload", 1);
    item[3].gun.left_reload.fill_frames("Textures/items/3/left", 1);
    item[3].gun.right_reload.fill_frames("Textures/items/3/right_reload", 1);




    item[3].gun.left.create(3, 100, 100, 50, 50, 0.1);
    item[3].gun.left.fill_frames("Textures/items/3/left", 1);
    item[3].gun.right.create(1, 100, 100, 50, 50, 0.1);
    item[3].gun.right.fill_frames("Textures/items/3/right", 1);

    item[3].gun.create(1, 20, 10, 40);
    item[3].gun.projectile.create(1, 40, 12, 0, 6, 0);
    item[3].gun.blast.create(2, 40, 40, 20, 20, 0.3);
    item[3].gun.projectile.fill_frames("Textures/items/3/bullet", 1);
    item[3].gun.blast.fill_frames("Textures/items/3/blast", 1);

    for (int i=0; i<8; i++)
    {
        item[3].gun.reload.frame_pos[i]=0.1;
        item[3].gun.left_reload.frame_pos[i]=0.1;
        item[3].gun.right_reload.frame_pos[i]=0.1;
    }
    for (int i=8; i<16; i++)
    {
        item[3].gun.reload.frame_pos[i]=1.1;
        item[3].gun.left_reload.frame_pos[i]=0.1;
        item[3].gun.right_reload.frame_pos[i]=1.1;
    }
    for (int i=16; i<24; i++)
    {
        item[3].gun.reload.frame_pos[i]=0.1;
        item[3].gun.left_reload.frame_pos[i]=0.1;
        item[3].gun.right_reload.frame_pos[i]=2.1;
    }
    for (int i=24; i<32; i++)
    {
        item[3].gun.reload.frame_pos[i]=1.1;
        item[3].gun.left_reload.frame_pos[i]=0.1;
        item[3].gun.right_reload.frame_pos[i]=1.1;
    }
    for (int i=32; i<40; i++)
    {
        item[3].gun.reload.frame_pos[i]=0.1;
        item[3].gun.left_reload.frame_pos[i]=0.1;
        item[3].gun.right_reload.frame_pos[i]=0.1;
    }

     for (int i=0; i<5; i++)
    {
        item[3].gun.animation.frame_pos[i]=0.5;
        item[3].gun.left.frame_pos[i]=0.5;
        item[3].gun.right.frame_pos[i]=0.5;
    }

    for (int i=5; i<10; i++)
    {
        item[3].gun.animation.frame_pos[i]=2.5;
        item[3].gun.left.frame_pos[i]=2.5;
        item[3].gun.right.frame_pos[i]=0.5;
    }
    for (int i=10; i<21; i++)
    {
        item[3].gun.animation.frame_pos[i]=1.5;
        item[3].gun.left.frame_pos[i]=1.5;
        item[3].gun.right.frame_pos[i]=0.5;
    }
    item[3].gun.pre.frame_pos[0]=0.1;
    item[3].gun.left_pre.frame_pos[0]=0.1;
    item[3].gun.right_pre.frame_pos[0]=0.1;


    item[3].gun.pre.frame_pos[1]=0.1;
    item[3].gun.left_pre.frame_pos[1]=0.1;
    item[3].gun.right_pre.frame_pos[1]=0.1;


    item[6].isStackable=false;

    item[6].setGun("Textures/items/6/gun", 2, 1, 200, 200, 40, 4, 0.1);
    //player.hands[3].left.create(3, 100, 100, 50, 50, 0.1);
    //player.hands[3].left.fill_frames("Textures/items/3/left", 1);

    item[6].gun.pre.create(1, 200, 200, 100, 100, 0.1);
    item[6].gun.left_pre.create(1, 100, 100, 50, 50, 0.1);
    item[6].gun.right_pre.create(1, 100, 100, 50, 50, 0.1);
    item[6].gun.reload.create(3, 200, 200, 100, 100, 0.1);
    item[6].gun.left_reload.create(1, 100, 100, 50, 50, 0.1);
    item[6].gun.right_reload.create(5, 100, 100, 50, 50, 0.1);

    item[6].gun.reload.fill_frames("Textures/items/6/reload", 1);
    item[6].gun.left_reload.fill_frames("Textures/items/6/left", 1);
    item[6].gun.right_reload.fill_frames("Textures/items/6/right_reload", 1);

    item[6].gun.left.create(2, 100, 100, 50, 50, 0.1);
    item[6].gun.left.fill_frames("Textures/items/6/left", 1);
    item[6].gun.right.create(2, 100, 100, 50, 50, 0.1);
    item[6].gun.right.fill_frames("Textures/items/6/right", 1);

    item[6].gun.create(1, 6, 10, 52);
    item[6].gun.projectile.create(1, 40, 12, 0, 6, 0);
    item[6].gun.blast.create(2, 40, 40, 20, 20, 0.3);
    item[6].gun.projectile.fill_frames("Textures/items/3/bullet", 1);
    item[6].gun.blast.fill_frames("Textures/items/3/blast", 1);

    for (int i=0; i<3; i++)
    {
        item[6].gun.animation.frame_pos[i]=0.5;
        item[6].gun.left.frame_pos[i]=0.5;
        item[6].gun.right.frame_pos[i]=0.5;
    }
    for (int i=3; i<7; i++)
    {
        item[6].gun.animation.frame_pos[i]=1.5;
        item[6].gun.left.frame_pos[i]=1.5;
        item[6].gun.right.frame_pos[i]=1.5;
    }

    item[6].gun.pre.frame_pos[0]=0.1;
    item[6].gun.left_pre.frame_pos[0]=0.1;
    item[6].gun.right_pre.frame_pos[0]=0.1;


    item[6].gun.pre.frame_pos[1]=0.1;
    item[6].gun.left_pre.frame_pos[1]=0.1;
    item[6].gun.right_pre.frame_pos[1]=0.1;

    item[6].gun.damage=20;
    item[6].gun.spread=0.05;
    item[6].gun.isPistol=false;



    for (int i=0; i<6; i++)
    {
        item[6].gun.reload.frame_pos[i]=0.1;
        item[6].gun.left_reload.frame_pos[i]=0.1;
        item[6].gun.right_reload.frame_pos[i]=3.1;
    }
    for (int i=6; i<12; i++)
    {
        item[6].gun.reload.frame_pos[i]=0.1;
        item[6].gun.left_reload.frame_pos[i]=0.1;
        item[6].gun.right_reload.frame_pos[i]=4.1;
    }
    for (int i=12; i<18; i++)
    {
        item[6].gun.reload.frame_pos[i]=0.1;
        item[6].gun.left_reload.frame_pos[i]=0.1;
        item[6].gun.right_reload.frame_pos[i]=3.1;
    }
    for (int i=18; i<26; i++)
    {
        item[6].gun.reload.frame_pos[i]=0.1;
        item[6].gun.left_reload.frame_pos[i]=0.1;
        item[6].gun.right_reload.frame_pos[i]=0.1;
    }
    for (int i=26; i<32; i++)
    {
        item[6].gun.reload.frame_pos[i]=1.1;
        item[6].gun.left_reload.frame_pos[i]=0.1;
        item[6].gun.right_reload.frame_pos[i]=1.1;
    }
    for (int i=32; i<40; i++)
    {
        item[6].gun.reload.frame_pos[i]=2.1;
        item[6].gun.left_reload.frame_pos[i]=0.1;
        item[6].gun.right_reload.frame_pos[i]=2.1;
    }
    for (int i=40; i<46; i++)
    {
        item[6].gun.reload.frame_pos[i]=1.1;
        item[6].gun.left_reload.frame_pos[i]=0.1;
        item[6].gun.right_reload.frame_pos[i]=1.1;
    }
    for (int i=46; i<53; i++)
    {
        item[6].gun.reload.frame_pos[i]=0.1;
        item[6].gun.left_reload.frame_pos[i]=0.1;
        item[6].gun.right_reload.frame_pos[i]=0.1;
    }
    item[7].isStackable=false;
    item[7].gun.isProjectile=false;

    item[7].setGun("Textures/items/7/gun", 2, 1, 200, 200, 0, 0, 0.1);
    item[7].gun.ammo_used=0;
    //player.hands[3].left.create(3, 100, 100, 50, 50, 0.1);
    //player.hands[3].left.fill_frames("Textures/items/3/left", 1);

    item[7].gun.pre.create(1, 200, 200, 100, 100, 0.1);
    item[7].gun.left_pre.create(1, 100, 100, 50, 50, 0.1);
    item[7].gun.right_pre.create(1, 100, 100, 50, 50, 0.1);
    item[7].gun.pre.fill_frames("Textures/items/7/pre", 1);
    item[7].gun.left_pre.fill_frames("Textures/items/7/left_pre", 1);
    item[7].gun.right_pre.fill_frames("Textures/items/3/right", 1);
    //item[7].gun.reload.create(2, 200, 200, 100, 100, 0.1);
    //item[7].gun.left_reload.create(1, 100, 100, 50, 50, 0.1);
    //item[7].gun.right_reload.create(3, 100, 100, 50, 50, 0.1);

    //item[7].gun.reload.fill_frames("Textures/items/3/reload", 1);
    //item[7].gun.left_reload.fill_frames("Textures/items/3/left", 1);
    //item[7].gun.right_reload.fill_frames("Textures/items/3/right_reload", 1);




    item[7].gun.left.create(2, 100, 100, 50, 50, 0.1);
    item[7].gun.left.fill_frames("Textures/items/7/left", 1);
    item[7].gun.right.create(1, 100, 100, 50, 50, 0.1);
    item[7].gun.right.fill_frames("Textures/items/3/right", 1);

    item[7].gun.create(5, 40, 10, 0);

    item[7].gun.max_distance=200;
    item[7].gun.pellets=1;
    item[7].gun.damage=30;
    item[7].gun.pellet_spread=0.1;

    item[7].gun.bullet_texture.loadFromFile("Textures/utility/empty.png");
    item[7].gun.bullet.setTexture(item[7].gun.bullet_texture);
    item[7].gun.bullet.setPosition(960, 540);

    for (int i=0; i<6; i++)
    {
        item[7].gun.pre.frame_pos[i]=0.1;
        item[7].gun.left_pre.frame_pos[i]=0.1;
        item[7].gun.right_pre.frame_pos[i]=0.1;
    }

    for (int i=35; i<41; i++)
    {
        item[7].gun.animation.frame_pos[i]=0.1;
        item[7].gun.left.frame_pos[i]=0.1;
        item[7].gun.right.frame_pos[i]=0.1;
    }
    for (int i=25; i<35; i++)
    {
        item[7].gun.animation.frame_pos[i]=1.1;
        item[7].gun.left.frame_pos[i]=1.1;
        item[7].gun.right.frame_pos[i]=1.1;
    }
    for (int i=0; i<25; i++)
    {
        item[7].gun.animation.frame_pos[i]=0.1;
        item[7].gun.left.frame_pos[i]=0.1;
        item[7].gun.right.frame_pos[i]=0.1;
    }
    //item[7].gun.projectile.create(1, 40, 12, 0, 6, 0);
    //item[7].gun.blast.create(2, 40, 40, 20, 20, 0.3);
    //item[7].gun.projectile.fill_frames("Textures/items/3/bullet", 1);
    //item[7].gun.blast.fill_frames("Textures/items/3/blast", 1);

    item[11].isStackable=false;

    item[11].setGun("Textures/items/11/gun", 3, 1, 200, 200, 30, 12, 0.1);
    //player.hands[3].left.create(3, 100, 100, 50, 50, 0.1);
    //player.hands[3].left.fill_frames("Textures/items/3/left", 1);

    item[11].gun.pre.create(1, 200, 200, 100, 100, 0.1);
    item[11].gun.left_pre.create(1, 100, 100, 50, 50, 0.1);
    item[11].gun.right_pre.create(1, 100, 100, 50, 50, 0.1);
    item[11].gun.reload.create(4, 200, 200, 100, 100, 0.1);
    item[11].gun.left_reload.create(1, 100, 100, 50, 50, 0.1);
    item[11].gun.right_reload.create(5, 100, 100, 50, 50, 0.1);

    item[11].gun.reload.fill_frames("Textures/items/11/reload", 1);
    item[11].gun.left_reload.fill_frames("Textures/items/11/left", 1);
    item[11].gun.right_reload.fill_frames("Textures/items/11/right_reload", 1);

    item[11].gun.left.create(2, 100, 100, 50, 50, 0.1);
    item[11].gun.left.fill_frames("Textures/items/11/left", 1);
    item[11].gun.right.create(2, 100, 100, 50, 50, 0.1);
    item[11].gun.right.fill_frames("Textures/items/11/right", 1);

    item[11].gun.create(1, 12, 15, 52);
    item[11].gun.projectile.create(1, 40, 12, 0, 6, 0);
    item[11].gun.blast.create(2, 40, 40, 20, 20, 0.3);
    item[11].gun.projectile.fill_frames("Textures/items/11/bullet", 1);
    item[11].gun.blast.fill_frames("Textures/items/3/blast", 1);

    for (int i=0; i<7; i++)
    {
        item[11].gun.animation.frame_pos[i]=0.5;
        item[11].gun.left.frame_pos[i]=0.5;
        item[11].gun.right.frame_pos[i]=0.5;
    }
    for (int i=3; i<13; i++)
    {
        item[11].gun.animation.frame_pos[i]=1.5;
        item[11].gun.left.frame_pos[i]=1.5;
        item[11].gun.right.frame_pos[i]=1.5;
    }

    item[11].gun.pre.frame_pos[0]=0.1;
    item[11].gun.left_pre.frame_pos[0]=0.1;
    item[11].gun.right_pre.frame_pos[0]=0.1;


    item[11].gun.pre.frame_pos[1]=0.1;
    item[11].gun.left_pre.frame_pos[1]=0.1;
    item[11].gun.right_pre.frame_pos[1]=0.1;

    item[11].gun.damage=45;
    item[11].gun.spread=0.05;
    item[11].gun.isPistol=false;



    for (int i=0; i<6; i++)
    {
        item[11].gun.reload.frame_pos[i]=0.1;
        item[11].gun.left_reload.frame_pos[i]=0.1;
        item[11].gun.right_reload.frame_pos[i]=3.1;
    }
    for (int i=6; i<12; i++)
    {
        item[11].gun.reload.frame_pos[i]=3.1;
        item[11].gun.left_reload.frame_pos[i]=0.1;
        item[11].gun.right_reload.frame_pos[i]=4.1;
    }
    for (int i=12; i<18; i++)
    {
        item[11].gun.reload.frame_pos[i]=0.1;
        item[11].gun.left_reload.frame_pos[i]=0.1;
        item[11].gun.right_reload.frame_pos[i]=3.1;
    }
    for (int i=18; i<26; i++)
    {
        item[11].gun.reload.frame_pos[i]=0.1;
        item[11].gun.left_reload.frame_pos[i]=0.1;
        item[11].gun.right_reload.frame_pos[i]=0.1;
    }
    for (int i=26; i<32; i++)
    {
        item[11].gun.reload.frame_pos[i]=1.1;
        item[11].gun.left_reload.frame_pos[i]=0.1;
        item[11].gun.right_reload.frame_pos[i]=1.1;
    }
    for (int i=32; i<40; i++)
    {
        item[11].gun.reload.frame_pos[i]=2.1;
        item[11].gun.left_reload.frame_pos[i]=0.1;
        item[11].gun.right_reload.frame_pos[i]=2.1;
    }
    for (int i=40; i<46; i++)
    {
        item[11].gun.reload.frame_pos[i]=1.1;
        item[11].gun.left_reload.frame_pos[i]=0.1;
        item[11].gun.right_reload.frame_pos[i]=1.1;
    }
    for (int i=46; i<53; i++)
    {
        item[11].gun.reload.frame_pos[i]=0.1;
        item[11].gun.left_reload.frame_pos[i]=0.1;
        item[11].gun.right_reload.frame_pos[i]=0.1;
    }


    Button resume;
    resume.create("Textures/utility/resume.png", "Textures/utility/resume.png", 860, 515, 200, 50);
    Button quit;
    quit.create("Textures/utility/quit1.png", "Textures/utility/quit2.png", 1770, 980, 100, 50);
    Button left_button;
    left_button.create("Textures/utility/button_left-1.png", "Textures/utility/button_left-2.png", 1520, 50, 100, 200);
    Button right_button;
    right_button.create("Textures/utility/button_right-1.png", "Textures/utility/button_right-2.png", 1820, 50, 100, 200);
    Button workshop_button;
    Button* level_button = new Button[levels_count];
    workshop_button.create("Textures/utility/workshop1.png", "Textures/utility/workshop2.png", 640, 740, 100, 100);
    Button craft;
    craft.create("Textures/utility/craft1.png", "Textures/utility/craft2.png", 1620, 300, 200, 50);



    for (int i=0; i<levels_count; i++)
    {
        std::string str1="Textures/utility/button";
        str1+=std::to_string(i+1);
        str1+="-1.png";
        std::string str2="Textures/utility/button";
        str2+=std::to_string(i+1);
        str2+="-2.png";
        level_button[i].create(str1, str2, 0, 0, 100, 100);
    }
    level_button[0].setPosition(880, 630);
    level_button[1].setPosition(1130, 550);
    level_button[2].setPosition(1130, 370);
    level_button[3].setPosition(960, 360);
    level_button[4].setPosition(860, 330);
    level_button[5].setPosition(790, 220);
    std::ofstream out;
    std::ifstream in;
    in.open("save.txt");
    //


        for (int i=0; i<items_count; i++)
        {
            in >> item[i].quantity;
        }
        in >> level_unlocked;
        for (int i=0; i<4; i++)
        {
            in >> player.slot[i].full >> player.slot[i].holding;
        }
        for (int i=0; i<blueprint_count; i++)
        {
            in >> blueprint[i].isOpen;
        }
        in >> player.health;
        for (int i=0; i<items_count; i++)
        {
            if (item[i].isWeapon)
            {
                in >> item[i].gun.ammo;
            }

        }
        for (int i=0; i<types_count; i++)
        {
            for (int j=0; j<enemy[i][0].quantity; j++)
            {
                in >> enemy[i][j].isBeaten;
            }
        }
    //
    in.close();
    for (int i=0; i<4; i++)
    {
        if (player.slot[i].full)
        {
            player.slot[i].button.texture1=item[player.slot[i].holding].button.texture1;
            player.slot[i].button.texture2=item[player.slot[i].holding].button.texture1;
        }
    }

    player.slot[0].button.sprite.setTextureRect(IntRect(0, 0, 100, 100));
    player.slot[1].button.sprite.setTextureRect(IntRect(0, 0, 100, 100));
    player.slot[2].button.sprite.setTextureRect(IntRect(0, 0, 100, 100));
    player.slot[3].button.sprite.setTextureRect(IntRect(0, 0, 100, 100));
    Texture workshop_texture;
    workshop_texture.loadFromFile("Textures/utility/workshop.png");
    Texture menu_texture;
    if (level_unlocked>6)
    {

    }
    else
    {
        menu_texture.loadFromFile("Textures/utility/menu1.png");
    }
    Sprite workshop_sprite;
    workshop_sprite.setTexture(workshop_texture);
    Sprite menu_sprite;
    menu_sprite.setTexture(menu_texture);

//Animation test;
//test.create(30, 100, 100);
//test.fill_frames("Textures/player/", 5);
//test.texture[0].loadFromFile("Textures/player/0.png");
//test.sprite.setPosition(100, 100);
//double a=-2;

/*Button test;
test.create("Textures/utility/button1.png", "Textures/utility/button2.png", 100, 100, 500, 100);*/
    //
    for (int i=0; i<items_count; i++)
    {
        //str+="\n\n";
        item[i].stats.setString(item[i].name);
    }

    Clock clock;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Guns 2", Style::Default);
    window.setSize(Vector2u(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));

    while (window.isOpen())
    {
        while (clock.getElapsedTime().asMicroseconds()<16667){}
        clock.restart();
        Vector2i pos=Mouse::getPosition(window);
        wheel=0;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type==Event::MouseWheelMoved)
{
    if (event.mouseWheel.delta<0)
    {
        wheel=1;
    }
    else if (event.mouseWheel.delta>0)
    {
        wheel=-1;
    }
}

            if (event.type == sf::Event::Closed)
                window.close();
        }


        //
        if (wasF11Pressed&&!Keyboard::isKeyPressed(Keyboard::F11))
            isF11Released=true;
        else
            isF11Released=false;
        if (Keyboard::isKeyPressed(Keyboard::F11))
            wasF11Pressed=true;
        else
            wasF11Pressed=false;

        if (isF11Released)
        {
            if (isFullScreen)
            {
                window.create(VideoMode(1920, 1080), "The Guns 2", Style::Default);
                isFullScreen=false;
            }
            else
            {
                window.create(VideoMode(1920, 1080), "The Guns 2", Style::Fullscreen);
                isFullScreen=true;
            }
            window.setSize(Vector2u(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
            window.setPosition(Vector2i(0, 0));
        }

        if (wasPressed&&!Mouse::isButtonPressed(Mouse::Left))
            isReleased=true;
        else
            isReleased=false;
        if (Mouse::isButtonPressed(Mouse::Left))
            wasPressed=true;
        else
            wasPressed=false;
            window.setView(stockview);
            window.clear();

        if (game_state==main_menu)
        {
            window.draw(menu_sprite);

            if (quit.isPointed(pos))
            {
                quit.expand();
                if (isReleased)
                {
                    window.close();
                }
            }
            else
            {
                quit.shrink();
            }
            window.draw(quit.sprite);
            if (workshop_button.isPointed(pos))
            {
                workshop_button.expand();
                if (isReleased)
                {
                    game_state=workshop;
                    //

                    //
                }
            }
            else
            {
                workshop_button.shrink();
            }
            window.draw(workshop_button.sprite);
            for (int i=0; i<levels_count; i++)
            {
                if (i<level_unlocked)
                {
                    if (level_button[i].isPointed(pos))
                    {
                        level_button[i].expand();
                        if (isReleased)
                        {
                            //


                            //
                            if (!player.slot[player.slot_holding].full)
                            {
                                player.slot_holding=0;
                                for (int j=0; j<4&&!player.slot[player.slot_holding].full; j++)
                                {
                                    player.slot_holding=(player.slot_holding+1)%4;
                                }
                            }

                            map_now=i;
                            game_state=game;
                            player.position.pos=mp[map_now].pos;
                            player.position.speed=mp[map_now].speed;
                            for (int j=0; j<enemy[0][0].quantity; j++)
                            {
                                enemy[0][j].health=0;
                                if (enemy[0][j].isSpawned[map_now]&&!enemy[0][j].isBeaten)
                                {
                                    enemy[0][j].position.pos.x=enemy[0][j].spawn[map_now].x;
                                    enemy[0][j].position.pos.y=enemy[0][j].spawn[map_now].y;
                                    enemy[0][j].position.speed.x=0;
                                    enemy[0][j].position.speed.y=0;
                                    enemy[0][j].health=enemy[0][j].max_health;
                                    enemy[0][j].pos_x=10;
                                    enemy[0][j].pos_y=0;
                                }
                            }
                            enemy[1][0].health=0;
                            if (enemy[1][0].isSpawned[map_now]&&!enemy[1][0].isBeaten)
                                {
                                    enemy[1][0].position.pos.x=enemy[1][0].spawn[map_now].x;
                                    enemy[1][0].position.pos.y=enemy[1][0].spawn[map_now].y;
                                    enemy[1][0].position.speed.x=0;
                                    enemy[1][0].position.speed.y=0;
                                    enemy[1][0].health=enemy[1][0].max_health;
                                    enemy[1][0].pos_x=10;
                                    enemy[1][0].pos_y=0;
                                }
                        }

                    }
                    else
                    {
                        level_button[i].shrink();
                    }
                    window.draw(level_button[i].sprite);
                }

            }


        }
        //workshop
        else if (game_state==workshop)
        {
            window.draw(workshop_sprite);
            blueprint[bluepr].sprite.setPosition(1620, 50);
            window.draw(blueprint[bluepr].sprite);
            if (left_button.isPointed(pos))
            {
                left_button.expand();
                if (isReleased)
                {
                    do
                    {
                        if (bluepr>0)
                        {
                            bluepr--;
                        }
                        else
                        {
                            bluepr=blueprint_count-1;
                        }
                    }
                    while(!blueprint[bluepr].isOpen);
                }
            }
            else
            {
                left_button.shrink();
            }
            window.draw(left_button.sprite);

            if (right_button.isPointed(pos))
            {
                right_button.expand();
                if (isReleased)
                {
                    do
                    {
                        if (bluepr<blueprint_count-1)
                        {
                            bluepr++;
                        }

                        else
                        {
                            bluepr=0;
                        }
                    }
                    while(!blueprint[bluepr].isOpen);
                }
            }
            else
            {
                right_button.shrink();
            }
            window.draw(right_button.sprite);

            bool can=true;
            int a1=0;
            std::string strng;
            text.setColor(Color::Red);
            for (; a1<blueprint[bluepr].ctr; a1++)
            {
                if (item[blueprint[bluepr].number[a1]].quantity<blueprint[bluepr].quantity[a1])
                {
                    can=false;
                }
                strng="x";
                strng+=std::to_string(blueprint[bluepr].quantity[a1]);
                strng+=" ";
                strng+=item[blueprint[bluepr].number[a1]].name;
                text.setString(strng);
                text.setPosition(1620, 375+a1*40);
                window.draw(text);
            }
            text.setColor(Color(0, 200, 0));

            text.setPosition(1620, 415+a1*40);
            strng="+ ";
            if (item[blueprint[bluepr].item_crafted].isStackable)
            {
                strng+="x";
                strng+=std::to_string(blueprint[bluepr].crafted_count);
                strng+=" ";

            }


            strng+=item[blueprint[bluepr].item_crafted].name;
            text.setString(strng);
            window.draw(text);


            if (!(item[blueprint[bluepr].item_crafted].isStackable||item[blueprint[bluepr].item_crafted].quantity<=0))
            {
                can=false;
            }

            if (craft.isPointed(pos))
            {
                craft.expand();
                if (isReleased)
                {
                    if (can==true)
                    {
                        for (int i=0; i<blueprint[bluepr].ctr; i++)
                        {
                            item[blueprint[bluepr].number[i]].quantity-=blueprint[bluepr].quantity[i];
                        }
                        item[blueprint[bluepr].item_crafted].quantity+=blueprint[bluepr].crafted_count;
                        out.open("save.txt");
                        for (int i=0; i<items_count; i++)
                        {
                                out << item[i].quantity << std::endl;
                        }
                        out << level_unlocked << std::endl;
                        for (int i=0; i<4; i++)
                        {
                            out << player.slot[i].full << std::endl << player.slot[i].holding << std::endl;
                        }
                        for (int i=0; i<blueprint_count; i++)
                        {
                            out << blueprint[i].isOpen << std::endl;
                        }
                        out << player.health << std::endl;
                        for (int i=0; i<items_count; i++)
                        {
                            if (item[i].isWeapon)
                            {
                                out << item[i].gun.ammo << std::endl;
                            }

                        }
                        for (int i=0; i<types_count; i++)
                        {
                            for (int j=0; j<enemy[i][0].quantity; j++)
                            {
                                out << enemy[i][j].isBeaten << std::endl;
                            }
                        }

                        out.close();
                    }
                }
            }
            else
            {
                craft.shrink();
            }
            window.draw(craft.sprite);
            int a=0;
            bool b=false;
            for (int i=0; i<items_count; i++)
            {
                if (item[i].quantity>0)
                {
                    if (item[i].button.isPointed(pos))
                    {
                        if (isReleased&&item[i].isWeapon)
                        {
                            int temp=player.canEquip();
                            bool cn=true;
                            for (int j=0; j<4; j++)
                            {
                                if (player.slot[j].holding==i&&player.slot[j].full)
                                {
                                    cn=false;
                                }
                            }
                            if (cn==true)
                            {
                                player.equip(i);
                                player.slot[temp].button.texture1=item[i].button.texture1;
                                player.slot[temp].button.texture2=item[i].button.texture1;
                                player.slot[temp].button.sprite.setTexture(player.slot[temp].button.texture1);
                                out.open("save.txt");
                                for (int k=0; k<items_count; k++)
                                {
                                    out << item[k].quantity << std::endl;
                                }
                                out << level_unlocked << std::endl;
                                for (int k=0; k<4; k++)
                                {
                                    out << player.slot[k].full << std::endl << player.slot[k].holding << std::endl;
                                }
                                for (int i=0; i<blueprint_count; i++)
                                {
                                    out << blueprint[i].isOpen << std::endl;
                                }
                                out << player.health << std::endl;
                                for (int i=0; i<items_count; i++)
                        {
                            if (item[i].isWeapon)
                            {
                                out << item[i].gun.ammo << std::endl;
                            }

                        }
                                for (int i=0; i<types_count; i++)
                        {
                            for (int j=0; j<enemy[i][0].quantity; j++)
                            {
                                out << enemy[i][j].isBeaten << std::endl;
                            }
                        }
                                out.close();

                            }


                        }
                        item[i].stats.setPosition(pos.x+20, pos.y+20);
                        b=true;
                        a=i;
                        item[i].button.expand();
                    }
                    else
                    {
                        item[i].button.shrink();
                    }
                        window.draw(item[i].button.sprite);
                    if (item[i].isStackable)
                    {
                        item[i].setText();
                        window.draw(item[i].text);
                    }



                }

            }
            for (int i=0; i<4; i++)
            {
                if (player.slot[i].button.isPointed(pos))
                {
                    player.slot[i].button.expand();
                    if (isReleased)
                    {
                        bool can1=false;
                        for (int j=0; j<4; j++)
                        {
                            if (j!=i&&player.slot[j].full)
                            {
                                can1=true;
                            }
                        }
                        if (can1)
                        {
                        player.unequip(i);
                        player.slot[i].button.texture1.loadFromFile("Textures/utility/empty.png");
                        player.slot[i].button.texture2.loadFromFile("Textures/utility/empty.png");
                        player.slot[i].button.sprite.setTexture(player.slot[i].button.texture2);
                        out.open("save.txt");
                        for (int i=0; i<items_count; i++)
                        {
                            out << item[i].quantity << std::endl;
                        }
                        out << level_unlocked << std::endl;
                        for (int i=0; i<4; i++)
                        {
                            out << player.slot[i].full << std::endl << player.slot[i].holding << std::endl;
                        }
                        for (int i=0; i<blueprint_count; i++)
                        {
                            out << blueprint[i].isOpen << std::endl;
                        }
                        out << player.health << std::endl;
                        for (int i=0; i<items_count; i++)
                        {
                            if (item[i].isWeapon)
                            {
                                out << item[i].gun.ammo << std::endl;
                            }

                        }
                        for (int i=0; i<types_count; i++)
                        {
                            for (int j=0; j<enemy[i][0].quantity; j++)
                            {
                                out << enemy[i][j].isBeaten << std::endl;
                            }
                        }

                        out.close();
                        }
                    }
                }
                else
                {
                    player.slot[i].button.shrink();
                }

            }
            window.draw(player.slot[0].sprite);
            window.draw(player.slot[1].sprite);
            window.draw(player.slot[2].sprite);
            window.draw(player.slot[3].sprite);
            window.draw(player.slot[0].button.sprite);
            window.draw(player.slot[1].button.sprite);
            window.draw(player.slot[2].button.sprite);
            window.draw(player.slot[3].button.sprite);
            if (b)
            {
                window.draw(item[a].stats);
            }


            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                game_state=main_menu;
            }

        }
        //game in.open(
        else if (game_state==game)
        {
            wasHealth=player.health;
            //Mouse::isButtonPressed
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                game_state=pause;
            }
            if (Keyboard::isKeyPressed(Keyboard::R)&&item[player.slot[player.slot_holding].holding].gun.reload_counter<1&&item[player.slot[player.slot_holding].holding].gun.ammo_used>0)
            {
                if (item[player.slot[player.slot_holding].holding].gun.ammo<item[player.slot[player.slot_holding].holding].gun.max_ammo&&item[item[player.slot[player.slot_holding].holding].gun.item_ammo].quantity>0)
                {
                    item[player.slot[player.slot_holding].holding].gun.reload_counter=item[player.slot[player.slot_holding].holding].gun.max_reload;
                }

            }


            if (wheel==1)
            {
                //std::cout << 1 << std::endl;

                player.slot_holding=(player.slot_holding+1)%4;
                for (int i=0; i<4&&!player.slot[player.slot_holding].full; i++)
                {
                    player.slot_holding=(player.slot_holding+1)%4;
                }
            }

            else if (wheel==-1)
            {
                //std::cout << -1 << std::endl;

                player.slot_holding=(player.slot_holding+3)%4;

                for (int i=0; i<4&&!player.slot[player.slot_holding].full; i++)
                {
                    player.slot_holding=(player.slot_holding+3)%4;
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Num1)&&player.slot[0].full)
            {
                player.slot_holding=0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Num2)&&player.slot[1].full)
            {
                player.slot_holding=1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Num3)&&player.slot[2].full)
            {
                player.slot_holding=2;
            }
            if (Keyboard::isKeyPressed(Keyboard::Num4)&&player.slot[3].full)
            {
                player.slot_holding=3;
            }
            for (int i=0; i<4; i++)
            {
                if (item[player.slot[i].holding].isWeapon&&player.slot_holding!=i)
                {
                    //item[i].gun.delay=0;
                    item[i].gun.predelay=0;
                    item[i].gun.reload_counter=0;
                    item[i].gun.deploy_counter=0;
                    //item[i].gun.animation.setFrame(0);
                    //item[i].gun.left.setFrame(0);
                    //item[i].gun.right.setFrame(0);
                }
            }
            if (((mp[map_now].M[round1(player.position.pos.x)-player.width-1][round1(player.position.pos.y)+player.height]>0&&player.position.speed.x<=-1&&mp[map_now].M[round1(player.position.pos.x)-player.width-1][round1(player.position.pos.y)+player.height-1]<=0)||(mp[map_now].M[round1(player.position.pos.x)+player.width+1][round1(player.position.pos.y)+player.height]>0&&player.position.speed.x>=1&&mp[map_now].M[round1(player.position.pos.x)+player.width+1][round1(player.position.pos.y)+player.height-1]<=0))&&player.position.speed.y>-1)
            {
                player.position.speed.y=-1;
                //player.position.speed.x=sign1(player.position.speed.x);
            }
            player.position.engine(player.head_height, player.height, player.width, mp[map_now]);
            player.position.speed.y+=gravity;




            int temp=round1(player.position.pos.x)+player.width;
            int temp2=round1(player.position.pos.y)+player.height+1;
            player.isStanding=false;
            for (int i=round1(player.position.pos.x)-player.width; i<=temp; i++)
            {
                for (int j=temp2; j<=temp2+2&&j<mp[map_now].height; j++)
                {
                    if (mp[map_now].M[i][j]>0)
                    {
                        player.isStanding=true;
                        break;
                    }
                }
            }
            if (player.isStanding)
            {
                if (player.position.speed.x>0)
                {
                    if (player.position.speed.x-friction<=0)
                    {
                        player.position.speed.x=0;
                    }
                    else
                    {
                        player.position.speed.x-=friction;
                    }
                }
                else if (player.position.speed.x<0)
                {
                    if (player.position.speed.x-friction>=0)
                    {
                        player.position.speed.x=0;
                    }
                    else
                    {
                        player.position.speed.x+=friction;
                    }
                }
            }//window.draw
            if (Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::A))
            {
                if (player.isStanding)
                {
                    if (player.position.speed.x-player.strafe_force>-player.max_speed*item[player.slot[player.slot_holding].holding].swiftness)
                    {
                        player.position.speed.x-=player.strafe_force;
                    }
                    else if (player.position.speed.x>-player.max_speed*item[player.slot[player.slot_holding].holding].swiftness)
                    {
                        player.position.speed.x=-player.max_speed*item[player.slot[player.slot_holding].holding].swiftness;
                    }
                }
                else
                {
                    if (player.position.speed.x-player.air_strafe_force>-player.max_speed*item[player.slot[player.slot_holding].holding].swiftness)
                    {
                        player.position.speed.x-=player.air_strafe_force;
                    }
                    else if (player.position.speed.x>-player.max_speed*item[player.slot[player.slot_holding].holding].swiftness)
                    {
                        player.position.speed.x=-player.max_speed*item[player.slot[player.slot_holding].holding].swiftness;
                    }
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::D))
            {
                if (player.isStanding)
                {
                    if (player.position.speed.x+player.strafe_force<player.max_speed*item[player.slot[player.slot_holding].holding].swiftness)
                    {
                        player.position.speed.x+=player.strafe_force;
                    }
                    else if (player.position.speed.x<player.max_speed*item[player.slot[player.slot_holding].holding].swiftness)
                    {
                        player.position.speed.x=player.max_speed*item[player.slot[player.slot_holding].holding].swiftness;
                    }
                }
                else
                {
                    if (player.position.speed.x+player.air_strafe_force<player.max_speed*item[player.slot[player.slot_holding].holding].swiftness)
                    {
                        player.position.speed.x+=player.air_strafe_force;
                    }
                    else if (player.position.speed.x<player.max_speed*item[player.slot[player.slot_holding].holding].swiftness)
                    {
                        player.position.speed.x=player.max_speed*item[player.slot[player.slot_holding].holding].swiftness;
                    }
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::W)||Keyboard::isKeyPressed(Keyboard::Up)||Keyboard::isKeyPressed(Keyboard::Space))
            {
                if (player.isStanding)
                {
                    player.position.speed.y-=player.jump_force*item[player.slot[player.slot_holding].holding].swiftness;
                }
            }
            if (Mouse::isButtonPressed(Mouse::Left)&&item[player.slot[player.slot_holding].holding].gun.delay<1&&item[player.slot[player.slot_holding].holding].gun.predelay<1&&item[player.slot[player.slot_holding].holding].gun.deploy_counter<1&&item[player.slot[player.slot_holding].holding].gun.reload_counter<1)
            {
                if (item[player.slot[player.slot_holding].holding].gun.ammo>=item[player.slot[player.slot_holding].holding].gun.ammo_used)
                {
                    item[player.slot[player.slot_holding].holding].gun.predelay=item[player.slot[player.slot_holding].holding].gun.max_predelay;
                }
                else if (item[item[player.slot[player.slot_holding].holding].gun.item_ammo].quantity>0&&item[player.slot[player.slot_holding].holding].gun.ammo_used>0)
                {
                    item[player.slot[player.slot_holding].holding].gun.reload_counter=item[player.slot[player.slot_holding].holding].gun.max_reload;
                }
            }

            player.tilt=-sign(player.body.pos-3)*(player.body.pos-3)/15+0.2;

            if ((player.position.speed.x<0.1&&player.position.speed.x>-0.1)||!player.isStanding)
            {
                player.tilt=0;
            }


            if (item[player.slot[player.slot_holding].holding].gun.predelay>0||item[player.slot[player.slot_holding].holding].gun.delay>0||item[player.slot[player.slot_holding].holding].gun.deploy_counter>0||item[player.slot[player.slot_holding].holding].gun.reload_counter>0)
            {
                player.tilt=0;
            }







            for (int i=0; i<4; i++)
            {
                if (player.slot_holding==i)
                {
                    player.slot[i].button.expand();
                }
                else
                {
                    player.slot[i].button.shrink();
                }
            }

            window.draw(mp[map_now].back_sprite);

            for (int i=0; i<mp[map_now].twidth; i++)
            {
                for (int j=0; j<mp[map_now].theight; j++)
                {
                    if (i*1920-1920<player.position.pos.x&&i*1920+1920>player.position.pos.x&&j*1080-1080<player.position.pos.y&&j*1080+1080>player.position.pos.y)
                    {
                        mp[map_now].sprite[i][j].setPosition(i*1920-player.position.pos.x, j*1080-player.position.pos.y);
                        window.draw(mp[map_now].sprite[i][j]);
                    }
                }
            }

            for (int i=0; i<projectile_count; i++)
            {
                if (enemy_projectile[i].damage<=0&&enemy_projectile[i].time)
                {
                    enemy_projectile[i].time--;
                    enemy_projectile[i].blast.setPR(1, round1(960-player.position.pos.x+enemy_projectile[i].x), round1(540-player.position.pos.y+enemy_projectile[i].y), 0);
                    window.draw(enemy_projectile[i].blast.sprite);
                    enemy_projectile[i].blast.step1();
                }
                if (enemy_projectile[i].damage>0)
                {//dist

                    Bullet bullet;
                    bullet.distance=0;
                    bullet=shoot(player.position.pos.x, player.position.pos.y, player.head_height, player.height, player.width, enemy_projectile[i].rotation, enemy_projectile[i].x, enemy_projectile[i].y, enemy_projectile[i].damage, enemy_projectile[i].speed, mp[map_now]);
                    if (bullet.distance<enemy_projectile[i].speed||enemy_projectile[i].distance_left<=0)
                    {
                        enemy_projectile[i].x+=(bullet.distance-1)*cos(enemy_projectile[i].rotation);
                        enemy_projectile[i].y+=(bullet.distance-1)*sin(enemy_projectile[i].rotation);
                        int dmg=damage(enemy_projectile[i].multiplier, player.position.pos.x, player.position.pos.y, player.width, player.position.pos.y-player.head_height, player.position.pos.y+player.height, enemy_projectile[i].x, enemy_projectile[i].y, enemy_projectile[i].radius, enemy_projectile[i].damage, mp[map_now].M);
                        player.health-=dmg;

                        player.position.speed.x+=enemy_projectile[i].knockback*cos(enemy_projectile[i].rotation)*double(dmg)/enemy_projectile[i].damage;
                        player.position.speed.y+=enemy_projectile[i].knockback*sin(enemy_projectile[i].rotation)*double(dmg)/enemy_projectile[i].damage;
                        enemy_projectile[i].damage=0;
                        enemy_projectile[i].blast.setPR(1, round1(960+enemy_projectile[i].x-player.position.pos.x), round1(540+enemy_projectile[i].y-player.position.pos.y), 0);
                    }
                    else
                    {
                        enemy_projectile[i].x+=cos(enemy_projectile[i].rotation)*(enemy_projectile[i].speed-1);
                        enemy_projectile[i].y+=sin(enemy_projectile[i].rotation)*(enemy_projectile[i].speed-1);
                        enemy_projectile[i].distance_left-=(enemy_projectile[i].speed-1);
                    }
                    enemy_projectile[i].animation.setPR(1, round1(960+enemy_projectile[i].x-player.position.pos.x), round1(540+enemy_projectile[i].y-player.position.pos.y), enemy_projectile[i].rotation);
                    window.draw(enemy_projectile[i].animation.sprite);
                }



            }






            for (int k=0; k<projectile_count; k++)
            {
                if (projectile[k].damage<=0&&projectile[k].time)
                {
                    projectile[k].time--;
                    projectile[k].blast.setPR(1, round1(960-player.position.pos.x+projectile[k].x), round1(540-player.position.pos.y+projectile[k].y), 0);
                    window.draw(projectile[k].blast.sprite);
                    projectile[k].blast.step1();
                }
                if (projectile[k].damage>0)
                {
                    int dist=9999;
                Bullet bullet;
                Bullet subbullet;
                bullet.distance=0;
                for (int i=0; i<types_count; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        if (enemy[i][j].health>0)
                        {
                            subbullet=shoot(enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, projectile[k].rotation, projectile[k].x, projectile[k].y, projectile[k].damage, projectile[k].speed, mp[map_now]);
                            if (subbullet.distance<dist)
                            {
                                bullet=subbullet;
                                dist=subbullet.distance;
                            }
                        }
                    }
                    if (dist==9999)
                    {
                        bullet=shoot(0, 0, 0, 0, 0, projectile[k].rotation, projectile[k].x, projectile[k].y, projectile[k].damage, projectile[k].speed, mp[map_now]);
                        dist=bullet.distance;
                    }

                }
                    //
                    if (dist<projectile[k].speed||projectile[k].distance_left<=0)
                    {
                        projectile[k].x+=(bullet.distance-1)*cos(projectile[k].rotation);
                        projectile[k].y+=(bullet.distance-1)*sin(projectile[k].rotation);
                        for (int i=0; i<types_count; i++)
                        {
                            for (int j=0; j<enemy[i][0].quantity; j++)
                            {
                                if (enemy[i][j].health>0)
                                {
                                    int dmg=damage(projectile[k].multiplier, enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].width, enemy[i][j].position.pos.y-enemy[i][j].head_height, enemy[i][j].position.pos.y+enemy[i][j].height, projectile[k].x, projectile[k].y, projectile[k].radius, projectile[k].damage, mp[map_now].M);
                                    enemy[i][j].health-=dmg;
                                    enemy[i][j].position.speed.x+=cos(projectile[k].rotation)*projectile[k].knockback*double(dmg)/projectile[k].damage;
                                    enemy[i][j].position.speed.y+=sin(projectile[k].rotation)*projectile[k].knockback*double(dmg)/projectile[k].damage;
                                }

                            }
                        }
                        projectile[k].damage=0;
                        //projectile[k].explosion.play();
                        projectile[k].blast.setPos(0.1);
                        projectile[k].blast.setPR(1, projectile[k].x, projectile[k].y, 0);
                        //window.draw(projectile[k].blast);
                    }
                    else
                    {
                        projectile[k].x+=cos(projectile[k].rotation)*(projectile[k].speed-1);
                        projectile[k].y+=sin(projectile[k].rotation)*(projectile[k].speed-1);
                        projectile[k].distance_left-=(projectile[k].speed-1);
                    }
                    //

                projectile[k].animation.setPR(1, 960+projectile[k].x-player.position.pos.x, 540+projectile[k].y-player.position.pos.y, projectile[k].rotation);
                projectile[k].animation.step1();
                window.draw(projectile[k].animation.sprite);
                projectile[k].speed+=projectile[k].acceleration;
                }


            }


            if (item[player.slot[player.slot_holding].holding].gun.predelay>0)
            {
                item[player.slot[player.slot_holding].holding].gun.predelay--;
                item[player.slot[player.slot_holding].holding].gun.pre.setFrame(item[player.slot[player.slot_holding].holding].gun.predelay);
                item[player.slot[player.slot_holding].holding].gun.left_pre.setFrame(item[player.slot[player.slot_holding].holding].gun.predelay);
                item[player.slot[player.slot_holding].holding].gun.right_pre.setFrame(item[player.slot[player.slot_holding].holding].gun.predelay);

                if (item[player.slot[player.slot_holding].holding].gun.predelay<1)
                {
                    //shoot
                    item[player.slot[player.slot_holding].holding].gun.ammo-=item[player.slot[player.slot_holding].holding].gun.ammo_used;

                    item[player.slot[player.slot_holding].holding].gun.delay=item[player.slot[player.slot_holding].holding].gun.max_delay;
                    double spread=random(item[player.slot[player.slot_holding].holding].gun.spread);
                    if (item[player.slot[player.slot_holding].holding].gun.isProjectile) // fire projectile(s)
                    {
                        int pr=-1;
                        for (int i=0; i<projectile_count; i++)
                        {
                            if (projectile[i].damage<=0&&projectile[i].time<=0)
                            {
                                pr=i;
                                break;
                            }
                        }
                        if (pr>=0)
                        {//launches a projectile
                            projectile[pr].multiplier=item[player.slot[player.slot_holding].holding].gun.splash_multiplier;
                            projectile[pr].animation=item[player.slot[player.slot_holding].holding].gun.projectile;
                            projectile[pr].time=item[player.slot[player.slot_holding].holding].gun.max_projectile_time;
                            projectile[pr].damage=item[player.slot[player.slot_holding].holding].gun.damage;
                            projectile[pr].speed=item[player.slot[player.slot_holding].holding].gun.proj_speed;
                            projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread;
                            projectile[pr].x=player.position.pos.x;
                            projectile[pr].y=player.position.pos.y;
                            projectile[pr].radius=item[player.slot[player.slot_holding].holding].gun.radius;
                            projectile[pr].distance_left=item[player.slot[player.slot_holding].holding].gun.max_distance;
                            projectile[pr].acceleration=item[player.slot[player.slot_holding].holding].gun.proj_acceleration;
                            projectile[pr].blast=item[player.slot[player.slot_holding].holding].gun.blast;
                            projectile[pr].blast.setPos(0.1);
                            projectile[pr].knockback=item[player.slot[player.slot_holding].holding].gun.knockback;

                        }
                        for (int i=1; i<=item[player.slot[player.slot_holding].holding].gun.pellets; i++)
                        {
                            pr=-1;
                        for (int i=0; i<projectile_count; i++)
                        {
                            if (projectile[i].damage<=0&&projectile[i].time<=0)
                            {
                                pr=i;
                                break;
                            }
                        }
                        if (pr>=0)
                        {//launches a projectile
                            projectile[pr].multiplier=item[player.slot[player.slot_holding].holding].gun.splash_multiplier;
                            projectile[pr].animation=item[player.slot[player.slot_holding].holding].gun.projectile;
                            projectile[pr].time=item[player.slot[player.slot_holding].holding].gun.max_projectile_time;
                            projectile[pr].damage=item[player.slot[player.slot_holding].holding].gun.damage;
                            projectile[pr].speed=item[player.slot[player.slot_holding].holding].gun.proj_speed;
                            projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread+i*item[player.slot[player.slot_holding].holding].gun.pellet_spread;
                            projectile[pr].x=player.position.pos.x;
                            projectile[pr].y=player.position.pos.y;
                            projectile[pr].radius=item[player.slot[player.slot_holding].holding].gun.radius;
                            projectile[pr].distance_left=item[player.slot[player.slot_holding].holding].gun.max_distance;
                            projectile[pr].acceleration=item[player.slot[player.slot_holding].holding].gun.proj_acceleration;
                            projectile[pr].blast=item[player.slot[player.slot_holding].holding].gun.blast;
                            projectile[pr].blast.setPos(0.1);
                            projectile[pr].knockback=item[player.slot[player.slot_holding].holding].gun.knockback;

                        }
                        pr=-1;
                        for (int i=0; i<projectile_count; i++)
                        {
                            if (projectile[i].damage<=0&&projectile[i].time<=0)
                            {
                                pr=i;
                                break;
                            }
                        }
                        if (pr>=0)
                        {//launches a projectile
                            projectile[pr].multiplier=item[player.slot[player.slot_holding].holding].gun.splash_multiplier;
                            projectile[pr].animation=item[player.slot[player.slot_holding].holding].gun.projectile;
                            projectile[pr].time=item[player.slot[player.slot_holding].holding].gun.max_projectile_time;
                            projectile[pr].damage=item[player.slot[player.slot_holding].holding].gun.damage;
                            projectile[pr].speed=item[player.slot[player.slot_holding].holding].gun.proj_speed;
                            projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread-i*item[player.slot[player.slot_holding].holding].gun.pellet_spread;
                            projectile[pr].x=player.position.pos.x;
                            projectile[pr].y=player.position.pos.y;
                            projectile[pr].radius=item[player.slot[player.slot_holding].holding].gun.radius;
                            projectile[pr].distance_left=item[player.slot[player.slot_holding].holding].gun.max_distance;
                            projectile[pr].acceleration=item[player.slot[player.slot_holding].holding].gun.proj_acceleration;
                            projectile[pr].blast=item[player.slot[player.slot_holding].holding].gun.blast;
                            projectile[pr].blast.setPos(0.1);
                            projectile[pr].knockback=item[player.slot[player.slot_holding].holding].gun.knockback;

                        }
                        }
                    }
                    else
                    {
                       int dist=9999;
                    Bullet bullet;
                    Bullet subbullet;
                    int ty=0;
                    int nb=0;

            for(int i=0; i<types_count; i++)
            {
                for (int j=0; j<enemy[i][0].quantity; j++)

                {
                    if (enemy[i][j].health>0)
                    {
                        subbullet=shoot(enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, spread+rotation(pos.x-960, pos.y-540), player.position.pos.x, player.position.pos.y, item[player.slot[player.slot_holding].holding].gun.damage, item[player.slot[player.slot_holding].holding].gun.max_distance, mp[map_now]);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            ty=i;
                            nb=j;
                            dist=subbullet.distance;
                        }
                    }

                }
            }
            if (dist==9999)
            {
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540), player.position.pos.x, player.position.pos.y, item[player.slot[player.slot_holding].holding].gun.damage, item[player.slot[player.slot_holding].holding].gun.max_distance, mp[map_now]);
            }
            if (bullet.hit)
            {
                enemy[ty][nb].health-=bullet.damage;
                item[player.slot[player.slot_holding].holding].gun.bullet.setScale(bullet.distance, sign1(pos.x-960));
                item[player.slot[player.slot_holding].holding].gun.bullet.setRotation(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y)*57);
            }
            else
            {
               item[player.slot[player.slot_holding].holding].gun.bullet.setScale(subbullet.distance, sign1(pos.x-960));
               item[player.slot[player.slot_holding].holding].gun.bullet.setRotation(rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y)*57);
            }
            item[player.slot[player.slot_holding].holding].gun.bullet.setPosition(960, 540);


            window.draw(item[player.slot[player.slot_holding].holding].gun.bullet);

            for (int k=1; k<=item[player.slot[player.slot_holding].holding].gun.pellets; k++)
            {
                dist=9999;
                for(int i=0; i<types_count; i++)
            {
                for (int j=0; j<enemy[i][0].quantity; j++)

                {
                    if (enemy[i][j].health>0)
                    {
                        subbullet=shoot(enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, spread+rotation(pos.x-960, pos.y-540)+k*item[player.slot[player.slot_holding].holding].gun.pellet_spread, player.position.pos.x, player.position.pos.y, item[player.slot[player.slot_holding].holding].gun.damage, item[player.slot[player.slot_holding].holding].gun.max_distance, mp[map_now]);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            ty=i;
                            nb=j;
                            dist=subbullet.distance;
                        }
                    }

                }
            }//player.tilt
            if (dist==9999)
            {
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)+k*item[player.slot[player.slot_holding].holding].gun.pellet_spread, player.position.pos.x, player.position.pos.y, item[player.slot[player.slot_holding].holding].gun.damage, item[player.slot[player.slot_holding].holding].gun.max_distance, mp[map_now]);
            }
            if (bullet.hit)
            {
                enemy[ty][nb].health-=bullet.damage;
                item[player.slot[player.slot_holding].holding].gun.bullet.setScale(bullet.distance, sign1(pos.x-960));
                item[player.slot[player.slot_holding].holding].gun.bullet.setRotation(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y)*57+k*item[player.slot[player.slot_holding].holding].gun.pellet_spread*57);
            }
            else
            {
               item[player.slot[player.slot_holding].holding].gun.bullet.setScale(subbullet.distance, sign1(pos.x-960));
               item[player.slot[player.slot_holding].holding].gun.bullet.setRotation(rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y)*57+k*item[player.slot[player.slot_holding].holding].gun.pellet_spread*57);
            }
            item[player.slot[player.slot_holding].holding].gun.bullet.setPosition(960, 540);


            window.draw(item[player.slot[player.slot_holding].holding].gun.bullet);
            dist=9999;
            for(int i=0; i<types_count; i++)
            {
                for (int j=0; j<enemy[i][0].quantity; j++)

                {
                    if (enemy[i][j].health>0)
                    {
                        subbullet=shoot(enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, spread+rotation(pos.x-960, pos.y-540)-k*item[player.slot[player.slot_holding].holding].gun.pellet_spread, player.position.pos.x, player.position.pos.y, item[player.slot[player.slot_holding].holding].gun.damage, item[player.slot[player.slot_holding].holding].gun.max_distance, mp[map_now]);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            ty=i;
                            nb=j;
                            dist=subbullet.distance;
                        }
                    }

                }
            }
            if (dist==9999)
            {
                //subbullet=shoot(0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540), player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                //subbullet=shoot(0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)+k*guns[player.gun_holding].pellet_spread, player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)-k*item[player.slot[player.slot_holding].holding].gun.pellet_spread, player.position.pos.x, player.position.pos.y, item[player.slot[player.slot_holding].holding].gun.damage, item[player.slot[player.slot_holding].holding].gun.max_distance, mp[map_now]);

            }
            if (bullet.hit)
            {
                enemy[ty][nb].health-=bullet.damage;
                item[player.slot[player.slot_holding].holding].gun.bullet.setScale(bullet.distance, sign1(pos.x-960));
                item[player.slot[player.slot_holding].holding].gun.bullet.setRotation(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y)*57-k*item[player.slot[player.slot_holding].holding].gun.pellet_spread*57);
            }
            else
            {
               item[player.slot[player.slot_holding].holding].gun.bullet.setScale(subbullet.distance, sign1(pos.x-960));
               item[player.slot[player.slot_holding].holding].gun.bullet.setRotation(rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y)*57-k*item[player.slot[player.slot_holding].holding].gun.pellet_spread*57);
            }
            item[player.slot[player.slot_holding].holding].gun.bullet.setPosition(960, 540);


            window.draw(item[player.slot[player.slot_holding].holding].gun.bullet);
            }

                    }
                    //

                    player.position.speed.x-=cos(rotation(pos.x-960, pos.y-540))*item[player.slot[player.slot_holding].holding].gun.self_knockback;
                    player.position.speed.y-=sin(rotation(pos.x-960, pos.y-540))*item[player.slot[player.slot_holding].holding].gun.self_knockback;
                }
            }
            if (item[player.slot[player.slot_holding].holding].gun.reload_counter>0)
            {
                item[player.slot[player.slot_holding].holding].gun.reload_counter--;
                item[player.slot[player.slot_holding].holding].gun.reload.setFrame(item[player.slot[player.slot_holding].holding].gun.reload_counter);
                item[player.slot[player.slot_holding].holding].gun.left_reload.setFrame(item[player.slot[player.slot_holding].holding].gun.reload_counter);
                item[player.slot[player.slot_holding].holding].gun.right_reload.setFrame(item[player.slot[player.slot_holding].holding].gun.reload_counter);
                if (item[player.slot[player.slot_holding].holding].gun.reload_counter<1)
                {
                    int temp_ammo=item[player.slot[player.slot_holding].holding].gun.max_ammo-item[player.slot[player.slot_holding].holding].gun.ammo;
                    if (temp_ammo>item[item[player.slot[player.slot_holding].holding].gun.item_ammo].quantity)
                    {
                        item[player.slot[player.slot_holding].holding].gun.ammo+=item[item[player.slot[player.slot_holding].holding].gun.item_ammo].quantity;
                        item[item[player.slot[player.slot_holding].holding].gun.item_ammo].quantity=0;
                    }
                    else
                    {
                        item[player.slot[player.slot_holding].holding].gun.ammo=item[player.slot[player.slot_holding].holding].gun.max_ammo;
                        item[item[player.slot[player.slot_holding].holding].gun.item_ammo].quantity-=temp_ammo;
                    }

                }
            }

            if (item[player.slot[player.slot_holding].holding].gun.predelay>0)
            {
                if (pos.x>=960)
                {

                    item[player.slot[player.slot_holding].holding].gun.pre.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.left_pre.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    item[player.slot[player.slot_holding].holding].gun.right_pre.setPR(1, 960, 540, player.tilt+!(item[player.slot[player.slot_holding].holding].gun.isPistol&&item[player.slot[player.slot_holding].holding].gun.reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    item[player.slot[player.slot_holding].holding].gun.pre.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.left_pre.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.right_pre.setPR(-1, 960, 540, -player.tilt+!(item[player.slot[player.slot_holding].holding].gun.isPistol&&item[player.slot[player.slot_holding].holding].gun.reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
                window.draw(item[player.slot[player.slot_holding].holding].gun.left_pre.sprite);
                window.draw(item[player.slot[player.slot_holding].holding].gun.pre.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(item[player.slot[player.slot_holding].holding].gun.right_pre.sprite);
            }
            else if (item[player.slot[player.slot_holding].holding].gun.reload_counter>0)
            {
                if (pos.x>=960)
                {

                    item[player.slot[player.slot_holding].holding].gun.reload.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.left_reload.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    item[player.slot[player.slot_holding].holding].gun.right_reload.setPR(1, 960, 540, player.tilt+!(item[player.slot[player.slot_holding].holding].gun.isPistol&&item[player.slot[player.slot_holding].holding].gun.reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    item[player.slot[player.slot_holding].holding].gun.reload.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.left_reload.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.right_reload.setPR(-1, 960, 540, -player.tilt+!(item[player.slot[player.slot_holding].holding].gun.isPistol&&item[player.slot[player.slot_holding].holding].gun.reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
                window.draw(item[player.slot[player.slot_holding].holding].gun.left_reload.sprite);
                window.draw(item[player.slot[player.slot_holding].holding].gun.reload.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(item[player.slot[player.slot_holding].holding].gun.right_reload.sprite);
            }
            else if (item[player.slot[player.slot_holding].holding].gun.deploy_counter>0)
            {
                if (pos.x>=960)
                {

                    item[player.slot[player.slot_holding].holding].gun.deploy.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.left_deploy.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    item[player.slot[player.slot_holding].holding].gun.right_deploy.setPR(1, 960, 540, player.tilt+!(item[player.slot[player.slot_holding].holding].gun.isPistol&&item[player.slot[player.slot_holding].holding].gun.reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    item[player.slot[player.slot_holding].holding].gun.deploy.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.left_deploy.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.right_deploy.setPR(-1, 960, 540, -player.tilt+!(item[player.slot[player.slot_holding].holding].gun.isPistol&&item[player.slot[player.slot_holding].holding].gun.reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
                window.draw(item[player.slot[player.slot_holding].holding].gun.left_deploy.sprite);
                window.draw(item[player.slot[player.slot_holding].holding].gun.deploy.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(item[player.slot[player.slot_holding].holding].gun.right_deploy.sprite);
            }
            else
            {
                if (pos.x>=960)
                {

                    item[player.slot[player.slot_holding].holding].gun.animation.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.left.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    item[player.slot[player.slot_holding].holding].gun.right.setPR(1, 960, 540, player.tilt+!(item[player.slot[player.slot_holding].holding].gun.isPistol&&item[player.slot[player.slot_holding].holding].gun.reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    item[player.slot[player.slot_holding].holding].gun.animation.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.left.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    item[player.slot[player.slot_holding].holding].gun.right.setPR(-1, 960, 540, -player.tilt+!(item[player.slot[player.slot_holding].holding].gun.isPistol&&item[player.slot[player.slot_holding].holding].gun.reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
                window.draw(item[player.slot[player.slot_holding].holding].gun.left.sprite);
                window.draw(item[player.slot[player.slot_holding].holding].gun.animation.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(item[player.slot[player.slot_holding].holding].gun.right.sprite);
            }
            for (int i=0; i<4; i++)
            {
                if (player.slot[i].full)
                {
                    if (item[player.slot[i].holding].gun.delay>0)
                    {
                        item[player.slot[i].holding].gun.delay--;
                        item[player.slot[i].holding].gun.animation.setFrame(item[player.slot[i].holding].gun.delay);
                        item[player.slot[i].holding].gun.left.setFrame(item[player.slot[i].holding].gun.delay);
                        item[player.slot[i].holding].gun.right.setFrame(item[player.slot[i].holding].gun.delay);
                    }
                }

            }






            //else if ()100

            for (int i=0; i<drop_count; i++)
            {
                if (drop[i].is)
                {
                    drop[i].position.engine(25, 25, 25, mp[map_now]);
                    drop[i].position.speed.y+=2;
                    if (mp[map_now].M[round1(drop[i].position.pos.x)][round1(drop[i].position.pos.y)+26]>0)
                    {
                        if (drop[i].position.speed.x<friction||-drop[i].position.speed.x>-friction)
                        {
                            drop[i].position.speed.x=0;
                        }
                        else
                        {
                            drop[i].position.speed.x-=friction*sign1(drop[i].position.speed.x);
                        }
                    }
                    if (player.position.pos.x-player.width-60<drop[i].position.pos.x&&player.position.pos.x+player.width+60>drop[i].position.pos.x&&player.position.pos.y-player.head_height-60<drop[i].position.pos.y&&player.position.pos.y+player.height>drop[i].position.pos.y)
                    {
                        drop[i].is=false;
                        item[drop[i].number].quantity++;
                    }
                    drop[i].sprite.setPosition(935+drop[i].position.pos.x-player.position.pos.x, 515+drop[i].position.pos.y-player.position.pos.y);
                    window.draw(drop[i].sprite);
                }
            }



                if (enemy[1][0].health>0)
                {

                    //enemy[0][i].position.engine(enemy[0][i].head_height, enemy[0][i].height, enemy[0][i].width, mp[map_now]);
                    //enemy[0][i].position.speed.y+=gravity;
                    //enemy[0][i].position.speed.x=0;window.draw window.draw


                    enemy[1][0].body.setPR(1, 960+enemy[1][0].position.pos.x-player.position.pos.x, 540+enemy[1][0].position.pos.y-player.position.pos.y, 0);
                    enemy[1][0].head.setPR(sign1(enemy[1][0].pos_x), 960+enemy[1][0].position.pos.x-player.position.pos.x, 540+enemy[1][0].position.pos.y-player.position.pos.y, rt(enemy[1][0].pos_x, enemy[1][0].pos_y));
                    if (enemy[1][0].position.pos.x>player.position.pos.x+2000||enemy[1][0].position.pos.x<player.position.pos.x-2000||enemy[1][0].position.pos.y>player.position.pos.y+2000||enemy[1][0].position.pos.y<player.position.pos.y-2000)
                    {
                        enemy[1][0].phase=0;
                        enemy[1][0].counter=180;
                        //enemy[1][0].body.setPos(0.1);
                    }
                    else
                    {
                        boss_h_sprite.setScale(1800.0*double(enemy[1][0].health)/enemy[1][0].max_health, 50);
                        window.draw(boss_h_sprite);
                        window.draw(boss_bar_sprite);
                    }
                    if (enemy[1][0].phase==0)
                    {
                        enemy[1][0].pos_x=player.position.pos.x-enemy[1][0].position.pos.x;
                        enemy[1][0].pos_y=player.position.pos.y-enemy[1][0].position.pos.y;
                        //enemy[1][0].body.setPos(0.1);
                        if (enemy[1][0].counter<1)
                        {
                            enemy[1][0].phase=1;
                            enemy[1][0].counter=30;

                            //enemy[0][i].body.setPos(1.1);
                        }
                    }
                    else if (enemy[1][0].phase==1)
                    {
                        //double temp_speed=sign1(player.position.pos.x-enemy[0][i].position.pos.x)*enemy[0][i].max_speed;
                        if (enemy[1][0].counter<1)
                        {
                            //shoot

                            int pr=-1;
                            for (int j=0; j<projectile_count; j++)
                            {
                                if (enemy_projectile[j].damage<=0&&enemy_projectile[j].time<=0)
                                {
                                    pr=j;
                                    break;
                                }
                            }
                            if (pr>=0)
                            { //enemy launches a projectile
                                enemy_projectile[pr].multiplier=1;
                                enemy_projectile[pr].animation=rocket;
                                enemy_projectile[pr].time=15;
                                enemy_projectile[pr].damage=100;
                                enemy_projectile[pr].speed=25;
                                enemy_projectile[pr].rotation=rotation(enemy[1][0].pos_x, enemy[1][0].pos_y);
                                enemy_projectile[pr].x=enemy[1][0].position.pos.x;
                                enemy_projectile[pr].y=enemy[1][0].position.pos.y;
                                enemy_projectile[pr].radius=200;
                                enemy_projectile[pr].distance_left=2000;
                                enemy_projectile[pr].acceleration=0;
                                enemy_projectile[pr].blast=explosion;
                                enemy_projectile[pr].blast.setPos(0.1);
                                enemy_projectile[pr].knockback=0;
                            }


                            //
                            enemy[1][0].head.pos=1;
                            enemy[1][0].phase=0;
                            enemy[1][0].counter=180;
                        }

                        //enemy[0][i].body.step1();

                    }



                    enemy[1][0].counter--;
                    if (enemy[1][0].head.pos>0.9)
                    {
                        enemy[1][0].head.step1();
                    }
                    enemy[1][0].wasDead=false;
                    window.draw(enemy[1][0].body.sprite);
                    window.draw(enemy[1][0].head.sprite);

                    if (enemy[1][0].position.pos.x-player.position.pos.x>1030)
                    {
                        x_boss=false;
                    }
                    else
                    {
                        if (x_boss==false)
                        {
                            for (int i=9113; i<9172; i++)
                            {
                                for (int j=540; j<792; j++)
                                {
                                    mp[0].M[i][j]=1;
                                }
                            }
                            for (int i=11374; i<11432; i++)
                            {
                                for (int j=797; j<1079; j++)
                                {
                                    mp[0].M[i][j]=1;
                                }
                            }
                        }
                        x_boss=true;

                    }
                    y_boss=true;
                }
                else
                {
                    if (enemy[1][0].wasDead==false)
                    {

                        enemy[1][0].death_counter=160;
                        enemy[1][0].isBeaten=true;
                        for (int j=0; j<3; j++)
                        {//100
                            int o=-1;
                            for (int k=0; k<drop_count; k++)
                            {
                                if (!drop[k].is)
                                {
                                    o=k;
                                    break;
                                }

                            }
                            if (o>=0)
                            {
                                drop[o].number=9;
                                drop[o].position.pos.x=enemy[1][0].position.pos.x;
                                drop[o].position.pos.y=enemy[1][0].position.pos.y;
                                drop[o].sprite.setTexture(item[9].button.texture1);
                                drop[o].sprite.setTextureRect(IntRect(0, 0, 100, 100));
                                drop[o].sprite.setScale(0.5, 0.5);
                                drop[o].is=true;
                                drop[o].position.speed.x=random(40);
                                drop[o].position.speed.y=-(rand()%30)-20;
                            }
                        }
                        for (int j=0; j<2; j++)
                        {//100
                            int o=-1;
                            for (int k=0; k<drop_count; k++)
                            {
                                if (!drop[k].is)
                                {
                                    o=k;
                                    break;
                                }

                            }
                            if (o>=0)
                            {
                                drop[o].number=10;
                                drop[o].position.pos.x=enemy[1][0].position.pos.x;
                                drop[o].position.pos.y=enemy[1][0].position.pos.y;
                                drop[o].sprite.setTexture(item[10].button.texture1);
                                drop[o].sprite.setTextureRect(IntRect(0, 0, 100, 100));
                                drop[o].sprite.setScale(0.5, 0.5);
                                drop[o].is=true;
                                drop[o].position.speed.x=random(40);
                                drop[o].position.speed.y=-(rand()%30)-20;
                            }
                        }
                        level_unlocked=2;
                        for (int i=11374; i<11432; i++)
                            {
                                for (int j=797; j<1079; j++)
                                {
                                    mp[0].M[i][j]=0;
                                }
                            }
                            for (int i=9113; i<9172; i++)
                            {
                                for (int j=540; j<792; j++)
                                {
                                    mp[0].M[i][j]=0;
                                }
                            }
                        /*int drp=int((rand()%300)*0.01)+1;

                        for (int j=0; j<drp; j++)
                        {//100
                            int o=-1;
                            for (int k=0; k<drop_count; k++)
                            {
                                if (!drop[k].is)
                                {
                                    o=k;
                                    break;
                                }

                            }
                            if (o>=0)
                            {
                                drop[o].number=0;
                                drop[o].position.pos.x=enemy[0][i].position.pos.x;
                                drop[o].position.pos.y=enemy[0][i].position.pos.y;
                                drop[o].sprite.setTexture(item[0].button.texture1);
                                drop[o].sprite.setTextureRect(IntRect(0, 0, 100, 100));
                                drop[o].sprite.setScale(0.5, 0.5);
                                drop[o].is=true;
                                drop[o].position.speed.x=random(30);
                                drop[o].position.speed.y=-(rand()%30)-10;
                            }
                        }
                        drp=int((rand()%200)*0.01)+1;
                        for (int j=0; j<drp; j++)
                        {
                            int o=-1;
                            for (int k=0; k<drop_count; k++)
                            {
                                if (!drop[k].is)
                                {
                                    o=k;
                                    break;
                                }

                            }
                            if (o>=0)
                            {
                                drop[o].number=4;
                                drop[o].position.pos.x=enemy[0][i].position.pos.x;
                                drop[o].position.pos.y=enemy[0][i].position.pos.y;
                                drop[o].sprite.setTexture(item[4].button.texture1);
                                drop[o].sprite.setTextureRect(IntRect(0, 0, 100, 100));
                                drop[o].sprite.setScale(0.5, 0.5);
                                drop[o].is=true;
                                drop[o].position.speed.x=random(30);
                                drop[o].position.speed.y=-(rand()%30)-10;
                            }
                        }
                        drp=int((rand()%300)*0.01);
                        for (int j=0; j<drp; j++)
                        {
                            int o=-1;
                            for (int k=0; k<drop_count; k++)
                            {
                                if (!drop[k].is)
                                {
                                    o=k;
                                    break;
                                }

                            }
                            if (o>=0)
                            {
                                drop[o].number=5;
                                drop[o].position.pos.x=enemy[0][i].position.pos.x;
                                drop[o].position.pos.y=enemy[0][i].position.pos.y;
                                drop[o].sprite.setTexture(item[5].button.texture1);
                                drop[o].sprite.setTextureRect(IntRect(0, 0, 100, 100));
                                drop[o].sprite.setScale(0.5, 0.5);
                                drop[o].is=true;
                                drop[o].position.speed.x=random(30);
                                drop[o].position.speed.y=-(rand()%30)-10;
                            }
                        }

                        drp=int((rand()%250)*0.01);
                        for (int j=0; j<drp; j++)
                        {
                            int o=-1;
                            for (int k=0; k<drop_count; k++)
                            {
                                if (!drop[k].is)
                                {
                                    o=k;
                                    break;
                                }

                            }
                            if (o>=0)
                            {
                                drop[o].number=8;
                                drop[o].position.pos.x=enemy[0][i].position.pos.x;
                                drop[o].position.pos.y=enemy[0][i].position.pos.y;
                                drop[o].sprite.setTexture(item[8].button.texture1);
                                drop[o].sprite.setTextureRect(IntRect(0, 0, 100, 100));
                                drop[o].sprite.setScale(0.5, 0.5);
                                drop[o].is=true;
                                drop[o].position.speed.x=random(30);
                                drop[o].position.speed.y=-(rand()%30)-10;
                            }
                        }*/
                    }
                    enemy[1][0].wasDead=true;
                    if (enemy[1][0].death_counter>0)
                    {
                        enemy[1][0].death.setPR(1, 960+enemy[1][0].position.pos.x-player.position.pos.x, 540+enemy[1][0].position.pos.y-player.position.pos.y, 0);
                        enemy[1][0].death.setFrame(enemy[1][0].death_counter);
                        window.draw(enemy[1][0].death.sprite);
                        enemy[1][0].death_counter--;
                    }
                }




            for (int i=0; i<10; i++)
            {
                if (enemy[0][i].health>0)
                {
                    enemy[0][i].position.engine(enemy[0][i].head_height, enemy[0][i].height, enemy[0][i].width, mp[map_now]);
                    enemy[0][i].position.speed.y+=gravity;
                    //enemy[0][i].position.speed.x=0;window.draw window.draw
                    int temp=round1(enemy[0][i].position.pos.x-enemy[0][i].width);
                    int temp2=round1(enemy[0][i].position.pos.y)+enemy[0][i].height+1;
                    enemy[0][i].isStanding=false;
                    for (int j=round1(enemy[0][i].position.pos.x)-enemy[0][i].width; j<=temp; j++)
                    {
                        if (mp[map_now].M[j][temp2]>0)
                        {
                            enemy[0][i].isStanding=true;
                            break;
                        }
                    }
                    if (enemy[0][i].isStanding)
                    {
                        if (enemy[0][i].position.speed.x>0)
                        {
                        if (enemy[0][i].position.speed.x-friction<=0)
                        {
                            enemy[0][i].position.speed.x=0;
                        }
                        else
                        {
                            enemy[0][i].position.speed.x-=friction;
                        }
                    }
                    else if (enemy[0][i].position.speed.x<0)
                    {
                        if (enemy[0][i].position.speed.x-friction>=0)
                        {
                            enemy[0][i].position.speed.x=0;
                        }
                        else
                        {
                            enemy[0][i].position.speed.x+=friction;
                        }
                }
            }
                    enemy[0][i].body.setPR(sign1(enemy[0][i].pos_x), 960+enemy[0][i].position.pos.x-player.position.pos.x, 540+enemy[0][i].position.pos.y-player.position.pos.y, 0);
                    enemy[0][i].head.setPR(sign1(enemy[0][i].pos_x), 960+enemy[0][i].position.pos.x-player.position.pos.x, 540+enemy[0][i].position.pos.y-player.position.pos.y, rt(enemy[0][i].pos_x, enemy[0][i].pos_y));
                    if (enemy[0][i].position.pos.x>player.position.pos.x+960||enemy[0][i].position.pos.x<player.position.pos.x-960||enemy[0][i].position.pos.y>player.position.pos.y+740||enemy[0][i].position.pos.y<player.position.pos.y-740)
                    {
                        enemy[0][i].phase=0;
                        enemy[0][i].counter=30;
                        enemy[0][i].body.setPos(0.1);
                    }
                    if (enemy[0][i].phase==0)
                    {
                        enemy[0][i].body.setPos(0.1);
                        if (enemy[0][i].counter<1)
                        {
                            enemy[0][i].phase=1;
                            enemy[0][i].counter=60;

                            enemy[0][i].body.setPos(1.1);
                        }
                    }
                    else if (enemy[0][i].phase==1)
                    {
                        //double temp_speed=sign1(player.position.pos.x-enemy[0][i].position.pos.x)*enemy[0][i].max_speed;
                        if (enemy[0][i].position.pos.x>player.position.pos.x+100||enemy[0][i].position.pos.x<player.position.pos.x-100)
                        {
                            if (sign1(player.position.pos.x-enemy[0][i].position.pos.x)*enemy[0][i].position.speed.x+enemy[0][i].strafe_force<enemy[0][i].max_speed)
                            {
                                enemy[0][i].position.speed.x+=sign1(player.position.pos.x-enemy[0][i].position.pos.x)*enemy[0][i].strafe_force;
                            }
                            else if (sign1(player.position.pos.x-enemy[0][i].position.pos.x)*enemy[0][i].position.speed.x<enemy[0][i].max_speed)
                            {
                                enemy[0][i].position.speed.x=sign1(player.position.pos.x-enemy[0][i].position.pos.x)*enemy[0][i].max_speed;
                            }
                        }
                        enemy[0][i].pos_x=player.position.pos.x-enemy[0][i].position.pos.x;
                        enemy[0][i].pos_y=player.position.pos.y-enemy[0][i].position.pos.y;
                        enemy[0][i].body.step1();
                        if (enemy[0][i].counter<1)
                        {
                            enemy[0][i].phase=2;
                            enemy[0][i].counter=90;
                        }
                    }
                    else if (enemy[0][i].phase==2)
                    {
                        enemy[0][i].body.setPos(0.1);
                        if (enemy[0][i].counter<1)
                        {
                            //shoot

                            int pr=-1;
                            for (int j=0; j<projectile_count; j++)
                            {
                                if (enemy_projectile[j].damage<=0&&enemy_projectile[j].time<=0)
                                {
                                    pr=j;
                                    break;
                                }
                            }
                            if (pr>=0)
                            { //enemy launches a projectile
                                enemy_projectile[pr].multiplier=1;
                                enemy_projectile[pr].animation=item[3].gun.projectile;
                                enemy_projectile[pr].time=5;
                                enemy_projectile[pr].damage=15;
                                enemy_projectile[pr].speed=250;
                                enemy_projectile[pr].rotation=rotation(enemy[0][i].pos_x, enemy[0][i].pos_y);
                                enemy_projectile[pr].x=enemy[0][i].position.pos.x;
                                enemy_projectile[pr].y=enemy[0][i].position.pos.y;
                                enemy_projectile[pr].radius=10;
                                enemy_projectile[pr].distance_left=1200;
                                enemy_projectile[pr].acceleration=0;
                                enemy_projectile[pr].blast=item[3].gun.blast;
                                enemy_projectile[pr].blast.setPos(0.1);
                                enemy_projectile[pr].knockback=6;
                            }
                            enemy[0][i].position.speed.x-=cos(enemy_projectile[pr].rotation)*10;
                            enemy[0][i].position.speed.y-=sin(enemy_projectile[pr].rotation)*10;

                            //
                            enemy[0][i].head.pos=1;
                            enemy[0][i].phase=3;
                            enemy[0][i].counter=10;
                        }
                    }
                    else if (enemy[0][i].phase==3)
                    {
                        enemy[0][i].body.pos=0.1;
                        if (enemy[0][i].counter<1)
                        {
                            enemy[0][i].phase=4;
                            enemy[0][i].counter=30;
                            enemy[0][i].body.setPos(1.1);
                        }
                    }
                    else if (enemy[0][i].phase==4)
                    {
                        enemy[0][i].body.step1();
                        if (enemy[0][i].position.pos.x>player.position.pos.x+100||enemy[0][i].position.pos.x<player.position.pos.x-100)
                        {
                            if (-sign1(player.position.pos.x-enemy[0][i].position.pos.x)*enemy[0][i].position.speed.x+enemy[0][i].strafe_force<enemy[0][i].max_speed)
                            {
                                enemy[0][i].position.speed.x-=sign1(player.position.pos.x-enemy[0][i].position.pos.x)*enemy[0][i].strafe_force;
                            }
                            else if (sign1(player.position.pos.x-enemy[0][i].position.pos.x)*enemy[0][i].position.speed.x<enemy[0][i].max_speed)
                            {
                                enemy[0][i].position.speed.x=-sign1(player.position.pos.x-enemy[0][i].position.pos.x)*enemy[0][i].max_speed;
                            }
                        }
                        enemy[0][i].pos_x=player.position.pos.x-enemy[0][i].position.pos.x;
                        enemy[0][i].pos_y=player.position.pos.y-enemy[0][i].position.pos.y;
                        if (enemy[0][i].counter<1)
                        {
                            enemy[0][i].phase=0;
                            enemy[0][i].counter=30;
                            enemy[0][i].body.setPos(0.1);
                        }
                    }
                    enemy[0][i].counter--;
                    if (enemy[0][i].head.pos>0.9)
                    {
                        enemy[0][i].head.step1();
                    }
                    enemy[0][i].wasDead=false;
                    window.draw(enemy[0][i].body.sprite);
                    window.draw(enemy[0][i].head.sprite);
                }
                else
                {
                    if (enemy[0][i].wasDead==false)
                    {
                        enemy[0][i].death_counter=30;
                        int drp=int((rand()%300)*0.01)+1;

                        for (int j=0; j<drp; j++)
                        {//100
                            int o=-1;
                            for (int k=0; k<drop_count; k++)
                            {
                                if (!drop[k].is)
                                {
                                    o=k;
                                    break;
                                }

                            }
                            if (o>=0)
                            {
                                drop[o].number=0;
                                drop[o].position.pos.x=enemy[0][i].position.pos.x;
                                drop[o].position.pos.y=enemy[0][i].position.pos.y;
                                drop[o].sprite.setTexture(item[0].button.texture1);
                                drop[o].sprite.setTextureRect(IntRect(0, 0, 100, 100));
                                drop[o].sprite.setScale(0.5, 0.5);
                                drop[o].is=true;
                                drop[o].position.speed.x=random(30);
                                drop[o].position.speed.y=-(rand()%30)-10;
                            }
                        }
                        drp=int((rand()%200)*0.01)+1;
                        for (int j=0; j<drp; j++)
                        {
                            int o=-1;
                            for (int k=0; k<drop_count; k++)
                            {
                                if (!drop[k].is)
                                {
                                    o=k;
                                    break;
                                }

                            }
                            if (o>=0)
                            {
                                drop[o].number=4;
                                drop[o].position.pos.x=enemy[0][i].position.pos.x;
                                drop[o].position.pos.y=enemy[0][i].position.pos.y;
                                drop[o].sprite.setTexture(item[4].button.texture1);
                                drop[o].sprite.setTextureRect(IntRect(0, 0, 100, 100));
                                drop[o].sprite.setScale(0.5, 0.5);
                                drop[o].is=true;
                                drop[o].position.speed.x=random(30);
                                drop[o].position.speed.y=-(rand()%30)-10;
                            }
                        }
                        drp=int((rand()%300)*0.01);
                        for (int j=0; j<drp; j++)
                        {
                            int o=-1;
                            for (int k=0; k<drop_count; k++)
                            {
                                if (!drop[k].is)
                                {
                                    o=k;
                                    break;
                                }

                            }
                            if (o>=0)
                            {
                                drop[o].number=5;
                                drop[o].position.pos.x=enemy[0][i].position.pos.x;
                                drop[o].position.pos.y=enemy[0][i].position.pos.y;
                                drop[o].sprite.setTexture(item[5].button.texture1);
                                drop[o].sprite.setTextureRect(IntRect(0, 0, 100, 100));
                                drop[o].sprite.setScale(0.5, 0.5);
                                drop[o].is=true;
                                drop[o].position.speed.x=random(30);
                                drop[o].position.speed.y=-(rand()%30)-10;
                            }
                        }

                        drp=int((rand()%250)*0.01);
                        for (int j=0; j<drp; j++)
                        {
                            int o=-1;
                            for (int k=0; k<drop_count; k++)
                            {
                                if (!drop[k].is)
                                {
                                    o=k;
                                    break;
                                }

                            }
                            if (o>=0)
                            {
                                drop[o].number=8;
                                drop[o].position.pos.x=enemy[0][i].position.pos.x;
                                drop[o].position.pos.y=enemy[0][i].position.pos.y;
                                drop[o].sprite.setTexture(item[8].button.texture1);
                                drop[o].sprite.setTextureRect(IntRect(0, 0, 100, 100));
                                drop[o].sprite.setScale(0.5, 0.5);
                                drop[o].is=true;
                                drop[o].position.speed.x=random(30);
                                drop[o].position.speed.y=-(rand()%30)-10;
                            }
                        }
                    }
                    enemy[0][i].wasDead=true;
                    if (enemy[0][i].death_counter>0)
                    {
                        enemy[0][i].death.setPR(1, 960+enemy[0][i].position.pos.x-player.position.pos.x, 540+enemy[0][i].position.pos.y-player.position.pos.y, 0);
                        enemy[0][i].death.setFrame(enemy[0][i].death_counter);
                        window.draw(enemy[0][i].death.sprite);
                        enemy[0][i].death_counter--;
                    }
                }


            }






            window.draw(player.slot[0].sprite);
            window.draw(player.slot[1].sprite);
            window.draw(player.slot[2].sprite);
            window.draw(player.slot[3].sprite);
            window.draw(player.slot[0].button.sprite);
            window.draw(player.slot[1].button.sprite);
            window.draw(player.slot[2].button.sprite);
            window.draw(player.slot[3].button.sprite);

            for (int i=0; i<4; i++)
            {
                if (player.slot[i].full)
                {
                    if (item[player.slot[i].holding].gun.max_ammo>0)
                    {
                        item[player.slot[i].holding].ammo_str="";
                        item[player.slot[i].holding].ammo_str+=std::to_string(item[player.slot[i].holding].gun.ammo);
                        item[player.slot[i].holding].ammo_str+="/";
                        item[player.slot[i].holding].ammo_str+=std::to_string(item[item[player.slot[i].holding].gun.item_ammo].quantity);
                        item[player.slot[i].holding].ammo.setString(item[player.slot[i].holding].ammo_str);
                        item[player.slot[i].holding].ammo.setPosition(1300+i*150, 1030);
                        window.draw(item[player.slot[i].holding].ammo);
                    }
                }
            }


            if (player.health<=0)
            {
                item[player.slot[player.slot_holding].holding].gun.delay=0;
                item[player.slot[player.slot_holding].holding].gun.deploy_counter=0;
                item[player.slot[player.slot_holding].holding].gun.reload_counter=0;
                item[player.slot[player.slot_holding].holding].gun.predelay=0;
                for (int i=0; i<types_count; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].death_counter=0;
                        enemy[i][j].wasDead=true;
                    }
                }
                player.head.setPos(0);
                for (int i=0; i<drop_count; i++)
                {
                    drop[i].is=false;
                }
                game_state=main_menu;

                in.open("save.txt");
                for (int i=0; i<items_count; i++)
                {
                    in >> item[i].quantity;
                }
                in >> level_unlocked;
                for (int i=0; i<4; i++)
                {
                    in >> player.slot[i].full >> player.slot[i].holding;
                }
                for (int i=0; i<blueprint_count; i++)
                {
                    in >> blueprint[i].isOpen;
                }
                in >> player.health;
                for (int i=0; i<items_count; i++)
                {
                    if (item[i].isWeapon)
                    {
                        in >> item[i].gun.ammo;
                    }

                }
                for (int i=0; i<types_count; i++)
        {
            for (int j=0; j<enemy[i][0].quantity; j++)
            {
                in >> enemy[i][j].isBeaten;
            }
        }
            in.close();
            }
            bool quit=false;
            int l=round1(player.position.pos.x+player.width);
            int l1=round1(player.position.pos.y+player.height);
            for (int i=round1(player.position.pos.x-player.width); i<l; i++)
            {
                for (int j=round1(player.position.pos.y-player.head_height); j<l1; j++)
                {
                    if (mp[map_now].M[i][j]==-1)
                    {
                        quit=true;
                        break;
                    }
                }
                if (quit)
                {
                    break;
                }
            }
            if (quit)
            {
                out.open("save.txt");
                        for (int i=0; i<items_count; i++)
                        {
                            out << item[i].quantity << std::endl;
                        }
                        out << level_unlocked << std::endl;
                        for (int i=0; i<4; i++)
                        {
                            out << player.slot[i].full << std::endl << player.slot[i].holding << std::endl;
                        }
                        for (int i=0; i<blueprint_count; i++)
                        {
                            out << blueprint[i].isOpen << std::endl;
                        }
                        out << player.health << std::endl;
                        for (int i=0; i<items_count; i++)
                        {
                            if (item[i].isWeapon)
                            {
                                out << item[i].gun.ammo << std::endl;
                            }

                        }
                        for (int i=0; i<types_count; i++)
                        {
                            for (int j=0; j<enemy[i][0].quantity; j++)
                            {
                                out << enemy[i][j].isBeaten << std::endl;
                            }
                        }

                        out.close();
                        player.head.setPos(0);
                        for (int i=0; i<drop_count; i++)
                {
                    drop[i].is=false;
                }
                        game_state=main_menu;
                        for (int i=0; i<types_count; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].death_counter=0;
                        enemy[i][j].wasDead=true;
                    }
                }
                item[player.slot[player.slot_holding].holding].gun.delay=0;
                item[player.slot[player.slot_holding].holding].gun.deploy_counter=0;
                item[player.slot[player.slot_holding].holding].gun.reload_counter=0;
                item[player.slot[player.slot_holding].holding].gun.predelay=0;
            }

            h_sprite.setScale(400*double(player.health)/player.max_health, 50);
            window.draw(h_sprite);
            window.draw(bar_sprite);
            if (player.health<wasHealth)
            {
                player.head.setPos(1.1);
            }
            if (player.head.pos>1)
            {
                player.head.step1();
            }
        }
        else if (game_state==pause)
        {
            window.draw(mp[map_now].back_sprite);
             for (int i=0; i<mp[map_now].twidth; i++)
            {
                for (int j=0; j<mp[map_now].theight; j++)
                {
                    if (i*1920-1920<player.position.pos.x&&i*1920+1920>player.position.pos.x&&j*1080-1080<player.position.pos.y&&j*1080+1080>player.position.pos.y)
                    {
                        window.draw(mp[map_now].sprite[i][j]);
                    }
                }
            }
            for (int i=0; i<projectile_count; i++)
            {
                if (enemy_projectile[i].damage<=0&&enemy_projectile[i].time)
                {
                    window.draw(enemy_projectile[i].blast.sprite);
                }
                if (enemy_projectile[i].damage>0)
                {
                    window.draw(enemy_projectile[i].animation.sprite);
                }
            }
            for (int k=0; k<projectile_count; k++)
            {
                if (projectile[k].damage<=0&&projectile[k].time)
                {
                    window.draw(projectile[k].blast.sprite);
                }
                if (projectile[k].damage>0)
                {
                    window.draw(projectile[k].animation.sprite);
                }
            }
            if (item[player.slot[player.slot_holding].holding].gun.predelay>0)
            {
                window.draw(item[player.slot[player.slot_holding].holding].gun.left_pre.sprite);
                window.draw(item[player.slot[player.slot_holding].holding].gun.pre.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(item[player.slot[player.slot_holding].holding].gun.right_pre.sprite);
            }
            else if (item[player.slot[player.slot_holding].holding].gun.reload_counter>0)
            {
                window.draw(item[player.slot[player.slot_holding].holding].gun.left_reload.sprite);
                window.draw(item[player.slot[player.slot_holding].holding].gun.reload.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(item[player.slot[player.slot_holding].holding].gun.right_reload.sprite);
            }
            else if (item[player.slot[player.slot_holding].holding].gun.deploy_counter>0)
            {
                window.draw(item[player.slot[player.slot_holding].holding].gun.left_deploy.sprite);
                window.draw(item[player.slot[player.slot_holding].holding].gun.deploy.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(item[player.slot[player.slot_holding].holding].gun.right_deploy.sprite);
            }
            else
            {
                window.draw(item[player.slot[player.slot_holding].holding].gun.left.sprite);
                window.draw(item[player.slot[player.slot_holding].holding].gun.animation.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(item[player.slot[player.slot_holding].holding].gun.right.sprite);
            }

            for (int i=0; i<10; i++)
            {
                if (enemy[0][i].health>0)
                {
                    window.draw(enemy[0][i].body.sprite);
                    window.draw(enemy[0][i].head.sprite);
                }
            }
            if (resume.isPointed(pos))
            {
                resume.expand();
                if (isReleased)
                {
                    game_state=game;
                }
            }
            else
            {
                resume.shrink();
            }
            window.draw(resume.sprite);

        }
            //a+=0.05;
        //test.step(0.4);
        //test.sprite.move(8, 0);

        //window.draw(test.sprite);
        /*if (test.isPointed(pos))
        {
            test.expand();
        }
        else
        {//out.open
            test.shrink();
        }
        window.draw(test.sprite);*/
        //out.open

        window.display();
    }

    return 0;
}
