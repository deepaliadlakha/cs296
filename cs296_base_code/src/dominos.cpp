/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"
//!Namespace for the project is CS296.

namespace cs296
{
  //!Elements in the Box2D Simulation World
  
  dominos_t::dominos_t()
  {
    //comment
    /*!<b>Ground</b>*/
    {
      b2EdgeShape shape;/*!<ol><li>Creates an instance of b2EdgeShape.</li>*/
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));/*!<li>Sets the Start and End Point of the b2EdgeShape as (-90,0) and (90,0) (in metres).</li>*/
      b2BodyDef bd;/*!<li>Creates an instance of b2BodyDef.</li>*/ 
      b2Body* b1 = m_world->CreateBody(&bd);/*!<li>Creates a pointer to the b2Body as returned by the method CreateBody of the Simulation World.</li>*/ 
      b1->CreateFixture(&shape, 0.0f);/*!<li>Creates the Shape Fixture with density 0 kg m per sec squared.</li></ol>*/
    }
      //comment
    /*!<b>Top horizontal shelf</b>*/
    {
      b2PolygonShape shape; /*!<ol><li>Creates an instance of b2PolygonShape.</li>*/
      shape.SetAsBox(6.0f, 0.25f);/*!<li>Converts the Polygon into the Box Shape with width 12 metres and height 0.5 metres.</li>*/
      b2BodyDef bd; /*!<li>Creates an instance of b2BodyDef.</li>*/
      bd.position.Set(-31.0f, 30.0f);/*!<li>Sets the position of the instance as (-31,30) (units in metres).</li>*/
      b2Body* ground = m_world->CreateBody(&bd);/*!<li>Creates a pointer to the b2Body as returned by the method CreateBody of the Simulation World.</li>*/
      ground->CreateFixture(&shape, 0.0f);/*!<li>Creates the Shape Fixture with density 0 kg m per sec squared.</li></ol>*/
    }
     //comment
    /*!<b>Dominos.</b>*/
    {
      b2PolygonShape shape; /*!<ol><li>Creates an instance of b2PolygonShape.</li>*/
      shape.SetAsBox(0.1f, 1.0f);/*!<li>Converts the Polygon into the Box Shape with width 0.2 metres and height 2 metres.</li>*/
	
      b2FixtureDef fd;/*!<li>Creates an instance of b2FixtureDef.</li>*/
      fd.shape = &shape;/*!<li>Defines the shape of the fixture as the instance of the b2PolygonShape created.</li>*/
      fd.density = 20.0f;/*!<li>Defines the density of the fixture as 20 kg m per sec squared.</li>*/
      fd.friction = 0.1f;/*!<li>Defines the coefficient of friction of the fixture as 0.1.</li>*/
      /*!<li>Creates ten instances of b2BodyDef (their type defined as dynamic) and positioned successively.</li>*/
      /*!<li>Creates fixtures of the instances of b2Body in the Simulation World.</li></ol>*/	
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
    //comment  
    /*!<b>Another horizontal shelf.</b>*/
    {
      b2PolygonShape shape; /*!<ol><li>Creates an instance of b2PolygonShape.</li>*/
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);/*!<li>Converts the Polygon into the Box Shape with width 0.2 metres and height 2 metres.</li>*/
	
      b2BodyDef bd;/*!<li>Creates an instance of b2BodyDef.</li>*/
      bd.position.Set(1.0f, 6.0f);/*!<li>Sets the position of the instance as (1,6) (units in metres).</li>*/
      b2Body* ground = m_world->CreateBody(&bd);/*!<li>Creates a pointer to the b2Body as returned by the method CreateBody of the Simulation World.</li>*/
      ground->CreateFixture(&shape, 0.0f);/*!<li>Creates the Shape Fixture with density 0 kg m per sec squared.</li></ol>*/
    }

    //comment
    /*!<b>The pendulum that knocks the dominos off.</b>*/
    {
      b2Body* b2;
      {
	b2PolygonShape shape;/*!<ol><li>Creates an instance of b2PolygonShape.</li>*/
	shape.SetAsBox(0.25f, 1.5f);/*!<li>Converts the Polygon into the Box Shape with width 0.5 metres and height 3 metres.</li>*/
	  
	b2BodyDef bd;/*!<li>Creates an instance of b2BodyDef.</li>*/
	bd.position.Set(-36.5f, 28.0f);/*!<li>Sets the position of the instance as (-36.5,28.0) (units in metres).</li>*/
	b2 = m_world->CreateBody(&bd);/*!<li>Creates a pointer to the b2Body as returned by the method CreateBody of the Simulation World.</li>*/
	b2->CreateFixture(&shape, 10.0f);/*!<li>Creates the Shape Fixture with density 10 kg m per sec squared.</li>*/
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;/*!<li>Creates an instance of b2PolygonShape.</li>*/
	shape.SetAsBox(0.25f, 0.25f);/*!<li>Converts the Polygon into the Box Shape with width 0.5 metres and height 0.5 metres.</li>*/
	  
	b2BodyDef bd;/*!<li>Creates an instance of b2BodyDef.</li>*/
	bd.type = b2_dynamicBody;/*!<li>Defines the type of the instance as dynamic.</li>*/
	bd.position.Set(-40.0f, 33.0f);/*!<li>Sets the position of the instance as (-40,33) (units in metres).</li>*/
	b4 = m_world->CreateBody(&bd);/*!<li>Creates a pointer to the b2Body as returned by the method CreateBody of the Simulation World.</li>*/
	b4->CreateFixture(&shape, 2.0f);/*!<li>Creates the Shape Fixture with density 2 kg m per sec squared.</li>*/
      }
	
      b2RevoluteJointDef jd;/*!<li>Creates an instance of b2RevoluteJointDef.</li>*/
      b2Vec2 anchor;/*!<li>Creates an instance of b2Vec2 (for the anchor).</li>*/
      anchor.Set(-37.0f, 40.0f);/*!<li>Sets the value of the b2Vector as (-37,40) (unit in metres).</li></ol>*/
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
     //comment 
    /*!<b>The train of small spheres</b>*/
    {
      b2Body* spherebody;/*!<ol><li>Creates an instance of b2Body.</li>*/
	
      b2CircleShape circle;/*!<li>Creates an instance of b2CircleShape.</li>*/
      circle.m_radius = 0.5;/*!<li>Defines the radius of the instance of the b2CircleShape as 0.5 metres.</li>*/
	
      b2FixtureDef ballfd;/*!<li>Creates an instance of b2FixtureDef.</li>*/
      ballfd.shape = &circle;/*!<li>Defines the shape of the instance of the b2FixtureDef as circle.</li>*/
      ballfd.density = 1.0f;/*!<li>Defines the density of the instance of the b2FixtureDef as 1 kg m per sec squared.</li>*/
      ballfd.friction = 0.0f;/*!<li>Defines the coefficient of friction of the instance of the b2FixtureDef as 0.</li>*/
      ballfd.restitution = 0.0f;/*!<li>Defines the coefficient of restitution of the instance of the b2FixtureDef as 0.</li>*/
      /*!<li>Creates ten instances of b2BodyDef (their type defined as dynamic) and positioned successively.</li>*/
      /*!<li>Creates fixtures of the instances of b2Body in the Simulation World.</li></ol>*/	
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
 //comment
    /*!<b>The pulley system</b>*/
    {
      b2BodyDef *bd = new b2BodyDef;/*!<ol><li>Creates a pointer to an instance of b2BodyDef.</li>*/
      bd->type = b2_dynamicBody;/*!<li>Defines the type of the instance as dynamic.</li>*/
      bd->position.Set(-10,15);/*!<li>Sets the position of the instance as (-10,15) (units in metres).</li>*/
      bd->fixedRotation = true;/*!<li>Enable rotation of the instance.</li>*/
      
      /*!<b>The open box</b>*/
      b2FixtureDef *fd1 = new b2FixtureDef;/*!<li>Creates a pointer to an instance of b2FixtureDef.</li>*/
      fd1->density = 10.0;/*!<li>Defines the density of the instance of the b2FixtureDef as 10 kg m per sec squared.</li>*/
      fd1->friction = 0.5;/*!<li>Defines the coefficient of friction of the instance of the b2FixtureDef as 0.5.</li>*/
      fd1->restitution = 0.f;/*!<li>Defines the coefficient of restitution of the instance of the b2FixtureDef as 0.</li>*/
      fd1->shape = new b2PolygonShape;/*!<li>Creates a pointer to an instance of b2PolygonShape.</li>*/
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;/*!<li>Creates a pointer to the second instance of b2FixtureDef.</li>*/
      fd2->density = 10.0;/*!<li>Defines the density of the second instance of the b2FixtureDef as 10 kg m per sec squared.</li>*/
      fd2->friction = 0.5;/*!<li>Defines the coefficient of friction of the second instance of the b2FixtureDef as 0.5.</li>*/
      fd2->restitution = 0.f;/*!<li>Defines the coefficient of restitution of the second instance of the b2FixtureDef as 0.</li>*/
      fd2->shape = new b2PolygonShape;/*!<li>Creates a pointer to an instance of b2PolygonShape.</li>*/
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;/*!<li>Creates a pointer to the third instance of b2FixtureDef.</li>*/
      fd3->density = 10.0;/*!<li>Defines the density of the third instance of the b2FixtureDef as 10 kg m per sec squared.</li>*/
      fd3->friction = 0.5;/*!<li>Defines the coefficient of friction of the third instance of the b2FixtureDef as 0.5.</li>*/
      fd3->restitution = 0.f;/*!<li>Defines the coefficient of restitution of the third instance of the b2FixtureDef as 0.</li>*/
      fd3->shape = new b2PolygonShape;/*!<li>Creates a pointer to an instance of b2PolygonShape.</li>*/
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1); /*!<li>Creates fixture of the first instance in the Simulation World.</li>*/	
      box1->CreateFixture(fd2); /*!<li>Creates fixture of the second instance in the Simulation World.</li>*/
      box1->CreateFixture(fd3); /*!<li>Creates fixture of the third instance in the Simulation World.</li>*/

      /*!<b>The bar</b>*/
      bd->position.Set(10,15);/*!<li>Sets the position of the instance of the b2BodyDef.</li>*/
      fd1->density = 34.0;/*!<li>Defines the density of the instance as 34 kg m per sec squared.</li>*/	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);/*!<li>Creates fixture of the third instance in the Simulation World.</li>*/

      /*!<b>The pulley joint</b>*/
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); /*!<li>Create Anchor point on body 1 in world axis.</li>*/
      b2Vec2 worldAnchorOnBody2(10, 15); /*!<li>Create Anchor point on body 2 in world axis.</li>*/
      b2Vec2 worldAnchorGround1(-10, 20); /*!<li>Create Anchor point for ground 1 in world axis.</li>*/
      b2Vec2 worldAnchorGround2(10, 20); /*!<li>Create Anchor point for ground 2 in world axis.</li></ol>*/
      float32 ratio = 1.0f; 
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }
     //comment
     /*!<b>The revolving horizontal platform</b>*/
    {
      b2PolygonShape shape;/*!<ol><li>Creates an instance of b2PolygonShape.</li>*/
      shape.SetAsBox(2.2f, 0.2f);/*!<li>Converts the Polygon into the Box Shape with width 4.4 metres and height 0.4 metres.</li>*/
	
      b2BodyDef bd;/*!<li>Creates an instance of b2BodyDef.</li>*/
      bd.position.Set(14.0f, 14.0f);/*!<li>Sets the position of the instance as (14,14) (units in metres).</li>*/
      bd.type = b2_dynamicBody;/*!<li>Defines the type of the instance as dynamic.</li>*/
      b2Body* body = m_world->CreateBody(&bd);/*!<li>Creates a pointer to the b2Body as returned by the method CreateBody of the Simulation World.</li>*/
      b2FixtureDef *fd = new b2FixtureDef;/*!<li>Creates a pointer to an instance of b2FixtureDef.</li>*/
      fd->density = 1.f;/*!<li>Defines the density of the instance as 34 kg m per sec squared.</li>*/
      fd->shape = new b2PolygonShape;/*!<li>Creates an instance of b2PolygonShape.</li>*/
      fd->shape = &shape;
      body->CreateFixture(fd);/*!<li>Creates fixture of the instance in the Simulation World.</li>*/

      b2PolygonShape shape2;/*!<li>Creates a second instance of b2PolygonShape.</li>*/
      shape2.SetAsBox(0.2f, 2.0f);/*!<li>Converts the Polygon into the Box Shape with width 0.4 metres and height 4 metres.</li>*/
      b2BodyDef bd2;/*!<li>Creates an instance of b2BodyDef.</li>*/
      bd2.position.Set(14.0f, 16.0f);/*!<li>Sets the position of the instance as (14,16) (units in metres).</li></ol>*/
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }
   //comment
    /*!<b>The heavy sphere on the platform</b>*/
    {
      b2Body* sbody;/*!<ol><li>Creates an instance of b2Body.</li>*/
      b2CircleShape circle;/*!<li>Creates an instance of b2PolygonShape.</li>*/
      circle.m_radius = 1.0;/*!<li>Defines the radius of the instance of b2PolygonShape as 1 metre.</li>*/
	
      b2FixtureDef ballfd;/*!<li>Creates an instance of b2FixtureDef.</li>*/
      ballfd.shape = &circle;/*!<li>Defines the shape of the instance of b2FixtureDef as a circle.</li>*/
      ballfd.density = 50.0f;/*!<li>Defines the density of the instance as 50 kg m per sec squared.</li>*/	 
      ballfd.friction = 0.0f;/*!<li>Defines the coefficient of friction of the instance as 0.</li>*/
      ballfd.restitution = 0.0f;/*!<li>Defines the coefficient of restitution of the instance as 0.</li>*/
      b2BodyDef ballbd;/*!<li>Creates an instance of b2BodyDef.</li>*/
      ballbd.type = b2_dynamicBody;/*!<li>Defines the type of the instance as dynamic.</li>*/
      ballbd.position.Set(14.0f, 18.0f);/*!<li>Sets the position of the instance as (14,18) (units in metres).</li>*/
      sbody = m_world->CreateBody(&ballbd);/*!<li>Creates a pointer to the b2Body as returned by the method CreateBody of the Simulation World.</li>*/ 
      sbody->CreateFixture(&ballfd);/*!<li>Creates the Fixture.</li></ol>*/
    }

	//comment
    /*!<b>The see-saw system at the bottom</b>*/
    {
      /*!&nbsp;  <b>The triangle wedge</b>*/
      b2Body* sbody;/*!<ol><li>Creates an instance of b2Body.</li>*/
      b2PolygonShape poly;/*!<li>Creates an instance of b2PolygonShape.</li>*/
      b2Vec2 vertices[3];/*!<li>Creates three instances of points.</li>*/
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);/*!<li>Set the three points as the vertices of the triangle.</li>*/
      b2FixtureDef wedgefd;/*!<li>Creates an instance of b2FixtureDef.</li>*/
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;/*!<li>Defines the density of the instance as 10 kg m per sec squared.</li>*/
      wedgefd.friction = 0.0f;/*!<li>Defines the coefficient of friction of the instance as 0.</li>*/
      wedgefd.restitution = 0.0f;/*!<li>Defines the coefficient of restitution of the instance as 0.</li>*/
      b2BodyDef wedgebd;/*!<li>Creates an instance of b2BodyDef.</li>*/
      wedgebd.position.Set(30.0f, 0.0f);/*!<li>Sets the position of the instance as (30,0) (units in metres).</li>*/
      sbody = m_world->CreateBody(&wedgebd);/*!<li>Creates a pointer to the b2Body as returned by the method CreateBody of the Simulation World.</li>*/ 
      sbody->CreateFixture(&wedgefd);/*!<li>Creates the Fixture.</li>*/

      /*!<b>The plank on top of the wedge</b>*/
      b2PolygonShape shape;/*!<li>Creates an instance of b2PolygonShape.</li>*/
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;/*!<li>Creates an instance of b2BodyDef.</li>*/
      bd2.position.Set(30.0f, 1.5f);/*!<li>Sets the position of the instance as (-40,33) (units in metres).</li>*/
      bd2.type = b2_dynamicBody;/*!<li>Defines the type of the instance as dynamic.</li>*/
      b2Body* body = m_world->CreateBody(&bd2);/*!<li>Creates a pointer to the b2Body as returned by the method CreateBody of the Simulation World.</li>*/ 
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;/*!<li>Defines the density of the instance as 1 kg m per sec squared.</li>*/
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);/*!<li>Creates the Fixture.</li>*/

      b2RevoluteJointDef jd;/*!<li>Creates an instance of b2RevoluteJointDef.</li>*/
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);/*!<li>Initializes the sbody, body and anchor using a world anchor point.*/
      m_world->CreateJoint(&jd);

      /*!<b>The light box on the right side of the see-saw</b>*/
      b2PolygonShape shape2;/*!<li>Creates an instance of b2PolygonShape.</li>*/
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;/*!<li>Creates an instance of b2BodyDef.</li>*/
      bd3.position.Set(40.0f, 2.0f);/*!<li>Set the position of the instance as (40,2) (units in metres).</li>*/
      bd3.type = b2_dynamicBody;/*!<li>Defines the type of the instance as dynamic.</li>*/
      b2Body* body3 = m_world->CreateBody(&bd3);/*!<li>Creates a pointer to the b2Body as returned by the method CreateBody of the Simulation World.</li>*/ 
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;/*!<li>Defines the density of the instance as 0.01 kg m per sec squared.</li>*/
      fd3->shape = new b2PolygonShape;/*!<li>Set the shape of the b2FixtureDef.</li>*/
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);/*!<li>Creates the Fixture.</li></ol>*/
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);//!Create a pointer to an instance of sim_t.
  /*!Assigning the value "Dominos" to the variable 'name' and "dominos_t::create" to variable 'create_fcn'*/
   
}
