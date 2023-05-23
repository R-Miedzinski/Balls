#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <math.h>
#include <vector>

bool Collision(sf::CircleShape a, sf::CircleShape b) {
double a_square = (a.getPosition().x+a.getRadius() - b.getPosition().x-b.getRadius())*(a.getPosition().x+a.getRadius() - b.getPosition().x-b.getRadius());
double b_square = (a.getPosition().y+a.getRadius() - b.getPosition().y-b.getRadius())*(a.getPosition().y+a.getRadius() - b.getPosition().y-b.getRadius());

if (sqrt(a_square + b_square) >= a.getRadius() + b.getRadius())
{

        return false;
}
else
{
return true;
}
}

class kolko
{
    public:
    double r;
    double v[2];
    double mass=1;
    sf::Color color;
    sf::CircleShape shape;
    std::vector<int> col_table;
    int check=0;

        double getxV()
        {
            return v[0];
        }
        double getyV()
        {
            return v[1];
        }
        double GetRadius()
        {
            return r;
        }
        void setRadius(double a)
        {
            r=a;
        }
        void setColor(sf::Color a)
        {
            color=a;
        }
        void setShape(sf::CircleShape a)
        {
            shape=a;
        }
        void setV(double vx, double vy)
        {
            v[0]=vx;
            v[1]=vy;
        }
        void addV(double dvx=0, double dvy=0)
        {
            v[0]+=dvx;
            v[1]+=dvy;
        }
        void Create()
        {
            shape = sf::CircleShape(r);
        }
        void setMass(double a)
        {
            mass=a;
        }
        double getMass()
        {
            return mass;
        }
        int CollisionCheck(int n)
        {
           return col_table[n-1];
        }
        void setColision(int n, int a=1)
        {
            col_table[n-1]=a;
        }
        void setColTable(int n)
        {
            for(int i=0;i<n;i++)
            col_table.push_back(0);
        }
};
sf::Vector2<double>* odbicie(kolko o1,kolko o2)
{
    static sf::Vector2<double> vec[2];
                     vec[0]=sf::Vector2<double>(((2*o2.getMass()*o2.getxV()+o1.getxV()*(o1.getMass()-o2.getMass()))/(o2.getMass()+o1.getMass())),
                     ((2*o2.getMass()*o2.getyV()+o1.getyV()*(o1.getMass()-o2.getMass()))/(o1.getMass()+o2.getMass())));
                     vec[1]=sf::Vector2<double>((2*o1.getMass()*o1.getxV()+o2.getxV()*(o2.getMass()-o1.getMass()))/(o2.getMass()+o1.getMass()),
                     (2*o1.getMass()*o1.getyV()+o2.getyV()*(o2.getMass()-o1.getMass()))/(o1.getMass()+o2.getMass()));
    return vec;
}
int main()
{


    int N=20;
    int W=1240, H=900;
    int box=0;
    double x[N],y[N];
    double vx=0.03, vy=-0.01;
    double g=0.00002;
    double dt=1,dt0;
    double radius=std::min(W/30,H/30);
    double spawn_table[N][3];
    sf::RenderWindow window(sf::VideoMode(W,H),"okno");
    sf::CircleShape shape(radius);
    kolko shapes[N];
    sf::Color kolor;


    int diff=0;
    double xtemp,ytemp;

    for(int i=0; i<N;i++)
    {

        std::cout<<"tworzenie kuli: "<<i<<std::endl;
        double counter=double(i)/(radius);
        diff=0;
        shapes[i].setRadius(5+counter*radius);
        kolor=sf::Color::Red;
        shapes[i].setMass(2*counter);
        while(box<i+1&&i!=0)
            {

            xtemp=rand()%(W-2*int(shapes[i].GetRadius()))+shapes[i].GetRadius();
            ytemp=rand()%(H-2*int(radius))+shapes[i].GetRadius();
            std::cout<<"wybor pozycji: "<<xtemp<<":"<<ytemp<<std::endl;
            for(int j=0;j<i;j++)
            {

                sf::CircleShape temp;
                temp.setRadius(5+counter*radius);
                temp.setPosition(xtemp,ytemp);
                if(Collision(shapes[j].shape,temp)==false)
                    {diff++;std::cout<<j<<" czysto"<<std::endl;}
                else{diff=0;std::cout<<"kolizja"<<std::endl;}

                if(diff==i)
                {
                    box++;
                }

            }
            diff=0;
            }
        if(i==0){xtemp=rand()%(W-2*int(shapes[i].GetRadius())-2)+shapes[i].GetRadius();
            ytemp=rand()%(H-2*int(radius)-2)+shapes[i].GetRadius();box++;}

        x[i]=xtemp;
        y[i]=ytemp;
        shapes[i].setColTable(N);
        shapes[i].Create();
        shapes[i].shape.setPosition(x[i],y[i]);
        shapes[i].shape.setFillColor(kolor);
        shapes[i].setV(vx,vy);
        std::cout<<x[i]<<";"<<y[i]<<std::endl;
    }
    double g0=g;
    dt0=dt;
    while(window.isOpen())
    {


    for(int i=0;i<N;i++)
        {
            shapes[i].shape.setPosition(x[i]-shapes[i].GetRadius(),y[i]-shapes[i].GetRadius());

        }

    sf::Event event;


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            dt=dt0-dt;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            g=g0-g;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
            {dt+=0.005;
            dt0=dt;std::cout<<dt<<std::endl;}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen))
            {dt-=0.005;
            dt0=dt;std::cout<<dt<<std::endl;}

        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                window.close();

        }



        window.clear(sf::Color::White);


            for(int i=0;i<N;i++)
            {




        if(shapes[i].shape.getPosition().x <=0||shapes[i].shape.getPosition().x >=W-2*shapes[i].GetRadius()){shapes[i].setV(-shapes[i].getxV(),shapes[i].getyV());}
        if(/*shapes[i].shape.getPosition().y <=0||*/shapes[i].shape.getPosition().y >=H-2*shapes[i].GetRadius()){shapes[i].setV(shapes[i].getxV(),-shapes[i].getyV()/1.005);}

        if(shapes[i].shape.getPosition().x>=W-2*shapes[i].GetRadius()){shapes[i].shape.setPosition(W-2*shapes[i].GetRadius(),shapes[i].shape.getPosition().y);}
        if(shapes[i].shape.getPosition().y>=H-2*shapes[i].GetRadius()){shapes[i].shape.setPosition(shapes[i].shape.getPosition().x,H-2*shapes[i].GetRadius());}
        if(shapes[i].shape.getPosition().x<=0){shapes[i].shape.setPosition(0,shapes[i].shape.getPosition().y);}
        //if(shapes[i].shape.getPosition().y<=0){shapes[i].shape.setPosition(shapes[i].shape.getPosition().x,0);}


            }

            for(int i=0;i<N;i++)
            {
                        for(int j=0; j<N ;j++)
        {
            if(j!=i)
            {
                    if(shapes[i].CollisionCheck(j)==0)
                    {
                    if(Collision(shapes[i].shape,shapes[j].shape))
                    {

                        double a=odbicie(shapes[i],shapes[j])[0].x;
                        double b=odbicie(shapes[i],shapes[j])[0].y;
                        double c=odbicie(shapes[i],shapes[j])[1].x;
                        double d=odbicie(shapes[i],shapes[j])[1].y;
                                shapes[i].setV(a,b);
                                shapes[j].setV(c,d);
                                shapes[j].setColision(i);
                    }
                    }
                    else{shapes[i].setColision(j,0);}

            }

        }
            }




    for(int i=0;i<N;i++)
    {
        window.draw(shapes[i].shape);
        x[i]=x[i]+shapes[i].getxV()*dt;
        y[i]=y[i]+shapes[i].getyV()*dt;
        shapes[i].addV(0,g*dt);
        shapes[i].color.r=255*(5*sqrt(shapes[i].getxV()*shapes[i].getxV()+shapes[i].getyV()*shapes[i].getyV()));
        //shapes[i].color.g=255*(10*sqrt(shapes[i].getxV()*shapes[i].getxV()+shapes[i].getyV()*shapes[i].getyV()));
        //shapes[i].color.b=255*(10*sqrt(shapes[i].getxV()*shapes[i].getxV()+shapes[i].getyV()*shapes[i].getyV()));
        shapes[i].shape.setFillColor(shapes[i].color);
    }

    window.display();
    }





    return 0;
}

