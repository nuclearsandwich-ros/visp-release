/****************************************************************************
 *
 * ViSP, open source Visual Servoing Platform software.
 * Copyright (C) 2005 - 2019 by Inria. All rights reserved.
 *
 * This software is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact Inria about acquiring a ViSP Professional
 * Edition License.
 *
 * See http://visp.inria.fr for more information.
 *
 * This software was developed at:
 * Inria Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 *
 * If you have questions regarding the use of this file, please contact
 * Inria at visp@inria.fr
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Description:
 * Le module "aritio.c" contient les procedures d'entree/sortie
 *		  des types definis dans le module "arit.h".
 *		  Les entrees non specifiees sont effectuees
 *		  sur le fichier "source" du module "lex.c".
 *		  Pour les mots cles des "fprintf_..." voir "token.c".
 *
 * Authors:
 * Jean-Luc CORRE
 *
 *****************************************************************************/

#ifndef vpAritio_h
#define vpAritio_h

#include <visp3/core/vpConfig.h>

#include <stdio.h>

#include "vpArit.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
void fprintf_Position(FILE *f, AritPosition *pp);
void fscanf_Point3f(Point3f *pp);
void fscanf_Vector(Vector *vp);
void fscanf_Position(AritPosition *pp);

#endif
#endif
