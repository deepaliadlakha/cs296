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


#ifndef _CS296BASE_HPP_
#define _CS296BASE_HPP_

#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>

#define	RAND_LIMIT 32767
//!Namespace for the project is CS296.
namespace cs296
{

  class base_sim_t;
  struct settings_t;
  typedef base_sim_t* sim_create_fcn(); 
  //! Struct that initialises the settings.
  /*!The value is set to 1 if we want the corresponding elements to be visible initially.*/
  						
     					
     					
     					
     					
     					
     					
     					
     					
     					
     					
     					
     					
     					
     					
     					
     					
     			

  
  struct settings_t
  {
   
    settings_t() :
      view_center(0.0f, 20.0f),					//!<Vector for center of the view (scene). Initialised to (0,20)
      hz(60.0f),								//!<Frequency of the Simulation. Initialised to 60Hz.
      velocity_iterations(8),					//!<Iterations count for the velocity phase.Initialised to 8 iterations.
      position_iterations(3),					//!<Iterations count for the position phase.Initialised to 3 iterations.
      draw_shapes(1),							//!<Draw_shapes option is checked initially in the GUI.
      draw_joints(1),							//!<Draw_joints option is checked initially in the GUI.
      draw_AABBs(0),							//!<Draw_AABBs option is unchecked initially in the GUI.
      draw_pairs(0),							//!<Draw_pairs option is unchecked initially in the GUI.
      draw_contact_points(0),					//!<Draw_contact_points option is set to invisible in the GUI.
      draw_contact_normals(0),					//!<Draw_contact_normal option is set to invisible in the GUI.
      draw_contact_forces(0),					//!<Draw_contact_forces option is set to invisible in the GUI.
      draw_friction_forces(0),					//!<Draw_friction_forces option is set to invisible in the GUI.
      draw_COMs(0),								//!<Draw_COMs option is unchecked initially in the GUI.
      draw_stats(0),							//!<Draw_stats option is unchecked initially in the GUI.
      draw_profile(0),							//!<Draw_profile option is unchecked initially in the GUI.
      enable_warm_starting(1),					//!<Enable_warm_starting option is set to visible in the GUI.
      enable_continuous(1),						//!<Enable_continuous option is set to visible in the GUI.
      enable_sub_stepping(0),					//!<Enable_sub_stepping option is set to invisible in the GUI.
      pause(0),									//!<Initially 'pause' is set to 0. 
      single_step(0)							//!<Increments simulation after clicking on 'single_step' button.
    {}
    
    b2Vec2 view_center;			//!<Sets the center in the form of Vectors. Its value has been initialised to (0,20) units being in metres. 
    float32 hz; 				//!<Sets the Frequency of the Simulation. Its value has been initialised to 60 Hz.
    int32 velocity_iterations;	//!<Sets the iteration count for the Velocity phase. Its value has been initialised to 8.
    int32 position_iterations;	//!<Sets the iteration count for the Position phase. Its value has been initialised to 3.
    int32 draw_shapes;			//!<Checks or unchecks the 'draw_shapes' option. Draw_shapes option is checked initially in the GUI.
    int32 draw_joints;			//!<Checks or unchecks the 'draw_joints' option. Draw_joints option is checked initially in the GUI.
    int32 draw_AABBs;			//!<Checks or unchecks the 'draw_AABBs' option. Draw_AABBs option is unchecked initially in the GUI.
    int32 draw_pairs;			//!<Checks or unchecks the 'draw_pairs' option. Draw_pairs option is unchecked initially in the GUI.
    int32 draw_contact_points;		//!<Changes the value of  the 'draw_contact_points' option. Draw_contact_points option is set to invisible in the GUI.
    int32 draw_contact_normals; 	//!<Changes the value of  the 'draw_contact_normals' option. Draw_contact_normal option is set to invisible in the GUI.
    int32 draw_contact_forces;		//!<Changes the value of  the 'draw_contact_forces' option. Draw_contact_forces option is set to invisible in the GUI.
    int32 draw_friction_forces;		//!<Changes the value of  the 'draw_friction_forces' option. Draw_friction_forces option is set to invisible in the GUI.
    int32 draw_COMs;			//!<Checks or unchecks the 'draw_COMs' option. Draw_COMs option is unchecked initially in the GUI.
    int32 draw_stats;			//!<Checks or unchecks the 'draw_stats' option. Draw_stats option is unchecked initially in the GUI.
    int32 draw_profile;			//!<Checks or unchecks the 'draw_profile' option. Draw_profile option is unchecked initially in the GUI.
    int32 enable_warm_starting;		//!<Changes the value of  the 'enable_warm_starting' option. Enable_warm_starting option is set to visible in the GUI.
    int32 enable_continuous;		//!<Changes the value of  the 'enable_continuous' option. Enable_continuous option is set to visible in the GUI.
    int32 enable_sub_stepping;		//!<Changes the value of  the 'enable_sub_stepping' option. Enable_sub_stepping option is set to invisible in the GUI.
    int32 pause;			//!<Changes the value of 'pause'. Called when 'pause' button is clicked. Initially 'pause' is set to 0. 
    int32 single_step;			//!<Jumps to the next step of simulation on being clicked. Increments simulation after clicking on 'single_step' button.
  };
  
  	//!Struct that initialises the simulation.
  	/*!This function assigns the variables, their values.These values are passed as arguments to the function.*/
  struct sim_t
  {
    const char *name;   //!<A variable of char type.
    sim_create_fcn *create_fcn; //!<A pointer to base_sim_t type.

    sim_t(const char *_name, sim_create_fcn *_create_fcn):
      name(_name), create_fcn(_create_fcn) {;}
  }; 
  
  extern sim_t *sim;
  
  
  const int32 k_max_contact_points = 2048;  
  struct contact_point_t			
  {
    b2Fixture* fixtureA;			//!<Stores the fixture of body A ,that is, its attributes like density etc.
    b2Fixture* fixtureB;			//!<Stores the fixture of body B ,that is, its attributes like friction etc.
    b2Vec2 normal;					//!<Stores the coordinates of the normal vector.
    b2Vec2 position;				//!<Stores the coordinates of the position vector.
    b2PointState state;				//!<Defines the state of the bodies.
  };
  //!<Struct used for contact between two bodies
  
  //!This is the class that defines the basis for simulation.
  /*!This class is inherited from b2ContactListener.
   * This class has functions that help the simulator in the GUI to take input from user
   * using keyboards and mouse.*/
  
  class base_sim_t : public b2ContactListener
  {
  public:
    
    base_sim_t();				//!<Defines the gravity vector and creates the World object.
    virtual ~base_sim_t();		//!<Deallocates the memory assigned to the World object. m_world is made to point to NULL.
    
    void set_text_line(int32 line) { m_text_line = line; }  //!<Prints strings like "****Paused***** when clicked on pause button
    void draw_title(int x, int y, const char *string);		//!<Draws title as pointed by string.
    b2World* get_world(void){
		return m_world;
	}
    
    virtual void step(settings_t* settings);   //!<Steps the simulation depending upon the settings selected.
												/*!If the game is paused, then we increase the time-step by 0.0 that is, nothing moves.
												 * Else if the game is not paused, then we increase the time-step depending on the 
												 * settings and draw all the objects again at their new position.
												 * We also increase the step-count by one*/
												
												
    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); }   //!<This function is not being used.
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); }//!<This function is not being used.

    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }//!<This function is not being used.
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }//!<This function is not being used.
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); }//!<This function is not being used.
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); }//!<This function is not being used.

    
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); } 		 	 //!<Called when joint is destroyed.
    virtual void begin_contact(b2Contact* contact) { B2_NOT_USED(contact); }		 //!<Called when two fixtures begin to touch.
    virtual void end_contact(b2Contact* contact) { B2_NOT_USED(contact); } 			 //!<Called when two fixtures cease to touch.
     //!This is called after a contact is updated.
    /*!It inspects a contact before it goes to the solver. We can also modify the contact manifolds and detect changes, as it stores a copy of the old manifold as well.*/
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold);	 																					   																			
//!This is called after the solver does its work.
    	/*!It helps us to inspect a contact after the solver is finished, and hence, is useful for inspection of impulses.*/
												
																																						  
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    }  																								

																						 

																						 

  protected:

   
    friend class contact_listener_t;
    
	
    b2Body* m_ground_body; 	//!<Defines the ground.
    b2AABB m_world_AABB;		//!<Defines the simulation world of AABB.
    contact_point_t m_points[k_max_contact_points];	//!<Vector to store the contact points between two bodies.
    int32 m_point_count;				//!<Stores the maximum number of contact points.

    debug_draw_t m_debug_draw;				//!<Used for drawing shapes in the world.
    int32 m_text_line;					//!<Stores the number of strings.
    b2World* m_world;					//!<Defines the world in which the simulation is to be done

    int32 m_step_count;					//!<Stores the maximum number of steps.
    
    b2Profile m_max_profile;				//!<Stores the maximum number of profiles.	
    b2Profile m_total_profile;				//!<Stores the total number of profiles.
  };
}

#endif
