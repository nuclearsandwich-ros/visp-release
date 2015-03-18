/****************************************************************************
 *
 * $Id: moveBiclops.cpp 4574 2014-01-09 08:48:51Z fspindle $
 *
 * This file is part of the ViSP software.
 * Copyright (C) 2005 - 2014 by INRIA. All rights reserved.
 * 
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * ("GPL") version 2 as published by the Free Software Foundation.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact INRIA about acquiring a ViSP Professional 
 * Edition License.
 *
 * See http://www.irisa.fr/lagadic/visp/visp.html for more information.
 * 
 * This software was developed at:
 * INRIA Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 * http://www.irisa.fr/lagadic
 *
 * If you have questions regarding the use of this file, please contact
 * INRIA at visp@inria.fr
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 * Description:
 *  Tests the control law
 * Authors:
 * Fabien Spindler
 *
 *****************************************************************************/
/*!
  \file moveBiclops.cpp

  \brief Example of a real robot control, the biclops robot (pan-tilt turret) by
  Traclabs. The robot is controlled first in position, then in velocity.

  See http://www.traclabs.com/tracbiclops.htm for more details.
*/


/*!
  \example moveBiclops.cpp

  Example of a real robot control, the biclops robot (pan-tilt turret) by
  Traclabs. The robot is controlled first in position, then in velocity.

  See http://www.traclabs.com/tracbiclops.htm for more details.
*/



#include <visp/vpParseArgv.h>
#include <visp/vpConfig.h>
#include <visp/vpDebug.h>
#include <visp/vpColVector.h>
#include <visp/vpTime.h>
#include <stdlib.h>
#ifdef VISP_HAVE_BICLOPS

#include <visp/vpRobotBiclops.h>

// List of allowed command line options
#define GETOPTARGS	"c:h"

/*

Print the program options.

  \param name : Program name.
  \param badparam : Bad parameter name.
  \param conf : Biclops configuration file.

*/
void usage(const char *name, const char *badparam, std::string conf)
{
  fprintf(stdout, "\n\
Move the biclops robot\n\
\n\
SYNOPSIS\n\
  %s [-c <Biclops configuration file>] [-h]\n						      \
", name);

  fprintf(stdout, "\n\
OPTIONS:                                               Default\n\
  -c <Biclops configuration file>                      %s\n\
     Sets the biclops robot configuration file.\n\n",
	  conf.c_str());

  if (badparam) {
    fprintf(stderr, "ERROR: \n" );
    fprintf(stderr, "\nBad parameter [%s]\n", badparam);
  }
}

/*!

Set the program options.

  \param argc : Command line number of parameters.
  \param argv : Array of command line parameters.
  \param conf : Biclops configuration file.
  
  \return false if the program has to be stopped, true otherwise.

*/
bool getOptions(int argc, const char **argv, std::string& conf)
{
  const char *optarg;
  int	c;
  while ((c = vpParseArgv::parse(argc, argv, GETOPTARGS, &optarg)) > 1) {

    switch (c) {
    case 'c': conf = optarg; break;
    case 'h': usage(argv[0], NULL, conf); return false; break;

    default:
      usage(argv[0], optarg, conf); return false; break;
    }
  }

  if ((c == 1) || (c == -1)) {
    // standalone param or error
    usage(argv[0], NULL, conf);
    std::cerr << "ERROR: " << std::endl;
    std::cerr << "  Bad argument " << optarg << std::endl << std::endl;
    return false;
  }

  return true;
}

int
main(int argc, const char ** argv)
{
  std::string opt_conf = "/usr/share/BiclopsDefault.cfg";

  // Read the command line options
  if (getOptions(argc, argv, opt_conf) == false) {
    exit (-1);
  }
  try {
    vpRobotBiclops robot(opt_conf.c_str());

    vpColVector q     (vpBiclops::ndof) ; // desired position
    vpColVector qdot  (vpBiclops::ndof) ; // desired velocity
    vpColVector qm    (vpBiclops::ndof) ; // measured position
    vpColVector qm_dot(vpBiclops::ndof) ; // measured velocity

    robot.setRobotState(vpRobot::STATE_POSITION_CONTROL) ;

    q = 0;
    q[0] = vpMath::rad(-10);
    q[1] = vpMath::rad(-20);
    vpCTRACE << "Set position in the articular frame: "
             << " pan: " << vpMath::deg(q[0]) << " deg"
             << " tilt: " << vpMath::deg(q[1]) << " deg" << std::endl ;
    robot.setPositioningVelocity(30.) ;
    robot.setPosition(vpRobot::ARTICULAR_FRAME, q) ;

    robot.getPosition(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Position in the articular frame: "
             << " pan: " << vpMath::deg(qm[0])
             << " tilt: " << vpMath::deg(qm[1]) << std::endl ;
    robot.getVelocity(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Velocity in the articular frame: "
             << " pan: " << vpMath::deg(qm[0])
             << " tilt: " << vpMath::deg(qm[1]) << std::endl ;

    vpCTRACE << "---------------------------------------- " << std::endl;

    q[0] = vpMath::rad(10);
    q[1] = vpMath::rad(20);
    vpCTRACE << "Set position in the articular frame: "
             << " pan: " << vpMath::deg(q[0]) << " deg"
             << " tilt: " << vpMath::deg(q[1]) << " deg" << std::endl ;
    robot.setPositioningVelocity(10) ;
    robot.setPosition(vpRobot::ARTICULAR_FRAME, q) ;

    robot.getPosition(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Position in the articular frame: "
             << " pan: " << vpMath::deg(qm[0])
             << " tilt: " << vpMath::deg(qm[1]) << std::endl ;
    robot.getVelocity(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Velocity in the articular frame: "
             << " pan: " << vpMath::deg(qm[0])
             << " tilt: " << vpMath::deg(qm[1]) << std::endl ;

    vpCTRACE << "---------------------------------------- " << std::endl;

    vpCTRACE << "Set STATE_VELOCITY_CONTROL" << std::endl;
    robot.setRobotState(vpRobot::STATE_VELOCITY_CONTROL) ;

    robot.getPosition(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Position in the articular frame: "
             << " pan: " << vpMath::deg(qm[0]) << " deg"
             << " tilt: " << vpMath::deg(qm[1]) << " deg" << std::endl ;
    robot.getVelocity(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Velocity in the articular frame: "
             << " pan: " << vpMath::deg(qm[0])
             << " tilt: " << vpMath::deg(qm[1]) << std::endl ;

    vpCTRACE << "---------------------------------------- " << std::endl;
    qdot = 0 ;
    //  qdot[0] = vpMath::rad(0.1) ;
    qdot[1] = vpMath::rad(25) ;
    vpCTRACE << "Set articular frame velocity "
             << " pan: " << vpMath::deg(qdot[0]) << " deg/s"
             << " tilt: " << vpMath::deg(qdot[1]) << " deg/s" << std::endl ;
    robot.setVelocity(vpRobot::ARTICULAR_FRAME, qdot) ;

    //waits 5000ms
    vpTime::wait(5000.0);

    robot.getPosition(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Position in the articular frame: "
             << " pan: " << vpMath::deg(qm[0]) << " deg"
             << " tilt: " << vpMath::deg(qm[1]) << " deg" << std::endl ;
    robot.getVelocity(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Velocity in the articular frame: "
             << " pan: " << vpMath::deg(qm[0])
             << " tilt: " << vpMath::deg(qm[1]) << std::endl ;


    vpCTRACE << "---------------------------------------- " << std::endl;
    qdot = 0 ;
    //  qdot[0] = vpMath::rad(0.1) ;
    qdot[1] = -vpMath::rad(25) ;
    vpCTRACE << "Set articular frame velocity "
             << " pan: " << vpMath::deg(qdot[0]) << " deg/s"
             << " tilt: " << vpMath::deg(qdot[1]) << " deg/s" << std::endl ;
    robot.setVelocity(vpRobot::ARTICULAR_FRAME, qdot) ;

    //waits 3000 ms
    vpTime::wait(3000.0);

    robot.getPosition(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Position in the articular frame: "
             << " pan: " << vpMath::deg(qm[0]) << " deg"
             << " tilt: " << vpMath::deg(qm[1]) << " deg" << std::endl ;
    robot.getVelocity(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Velocity in the articular frame: "
             << " pan: " << vpMath::deg(qm[0])
             << " tilt: " << vpMath::deg(qm[1]) << std::endl ;


    vpCTRACE << "---------------------------------------- " << std::endl;


    qdot = 0 ;
    //  qdot[0] = vpMath::rad(0.1) ;
    qdot[1] = vpMath::rad(10) ;
    vpCTRACE << "Set articular frame velocity "
             << " pan: " << vpMath::deg(qdot[0]) << " deg/s"
             << " tilt: " << vpMath::deg(qdot[1]) << " deg/s" << std::endl ;
    robot.setVelocity(vpRobot::ARTICULAR_FRAME, qdot) ;

    //waits 2000 ms
    vpTime::wait(2000.0);

    robot.getPosition(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Position in the articular frame: "
             << " pan: " << vpMath::deg(qm[0]) << " deg"
             << " tilt: " << vpMath::deg(qm[1]) << " deg" << std::endl ;
    robot.getVelocity(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Velocity in the articular frame: "
             << " pan: " << vpMath::deg(qm[0])
             << " tilt: " << vpMath::deg(qm[1]) << std::endl ;

    vpCTRACE << "---------------------------------------- " << std::endl;

    qdot = 0 ;
    qdot[0] = vpMath::rad(-5);
    //qdot[1] = vpMath::rad(-5);

    vpCTRACE << "Set articular frame velocity "
             << " pan: " << vpMath::deg(qdot[0]) << " deg/s"
             << " tilt: " << vpMath::deg(qdot[1]) << " deg/s" << std::endl ;
    robot.setVelocity(vpRobot::ARTICULAR_FRAME, qdot) ;

    //waits 2000 ms
    vpTime::wait(2000.0);

    robot.getPosition(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Position in the articular frame: "
             << " pan: " << vpMath::deg(qm[0]) << " deg"
             << " tilt: " << vpMath::deg(qm[1]) << " deg" << std::endl ;
    robot.getVelocity(vpRobot::ARTICULAR_FRAME, qm) ;
    vpCTRACE << "Velocity in the articular frame: "
             << " pan: " << vpMath::deg(qm[0])
             << " tilt: " << vpMath::deg(qm[1]) << std::endl ;
  }
  catch(...) {

  }

}
#else
int
main()
{
  vpERROR_TRACE("You do not have a biclops robot connected to your computer...");
  return 0; 
}

#endif