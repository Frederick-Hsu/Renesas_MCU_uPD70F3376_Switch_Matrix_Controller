/***************************************************************************************************
 * Prject name	: Switch_Matrix_Controllerr
 *
 * Program name	: version.h
 * Description	: Dedicatedly show the revision history in this independent file.
 * Author	: XU ZAN
 * Date		: Fri.	July 27, 2012
 * Copyright(C)		2010 --- 2020
 * All rights reserved.
 *
 ***************************************************************************************************/

#ifndef _VERSION_H
#define _VERSION_H

	#define YES	1
	#define NO	0
	
	#define VERSION_UPGRADE		YES
	
	
	/*
	 * [Very Important :]
	 *
	 * Software version-upgrading rule :
	 *
	 * 		| Main revision	| Minor revision | Release| Build   |
	 *	--------+---------------+----------------+--------+---------+
	 *	 Digits |     x.        |      xx.       |  x.    |  xx     |
	 *	--------+---------------+----------------+--------+---------+
	 *	 For example : 1.05.5.02     			            |
	 *	--------+---------------+----------------+--------+---------+
	 *	        |     1.        |     05.        |  5.    |  02     |
	 *	--------+---------------+----------------+--------+---------+
	 *	
	 * 1. Before the preliminary master release, the main revision should be kept 0.
	 *
	 * 2. When you want to release 1st master version, please upgrade the main revision to 1.
	 *
	 * 3. Before the next master release, never modify current main revision, just upgrade the minor revision.
	 *
	 * 4. The minor revision should increase 1 for each time release.
	 *
	 * 5. For each master release, the main revision upgrading should be determined by project team leader and SW regulator co-discussion. 
	 *    In general, main revision increased 1 for each master release.
	 *
	 * 6. The "Release" indicates that current release is the Nth release.
	 *
	 * 7. When you want to release a beta (or testing) version, just for the purpose of debugging or other experimental testing, 
	 *    please add a mark after minor version. For instance : 2.03b.5.02    The mark 'b' indicates 'beta'.
	 *
	 * 8. When you want to issue the .hex file, please append the suffix _version_buildtime.hex of current version and build time.
	 *    For example : Switch_Matrix_Controller_1.05.5.02_20120727.hex
	 *    If possible, you should append the checksum value for the .hex file.
	 *
	 * 9. When you want to upgrade the version, you should move the last "CURRENT_VERSION" to the "PREVIOUS_VERSION", meanwhile, disable your last "CURRENT_VERSION",
	 *    insert a new "CURRENT_VERSION". 
	 *    But, please never remove or erase your last "CURRENT_VERSION".
	 *    Please keep and record all version-upgrading history in this dedicated file.
	 *
	 * 10. Please strictly obey the software version-upgrading rule.
	 *
	 *
	 *
	 * Remarked by XU ZAN @2012-07-27
	 */
	
	#define MILESTONE_FLAG
	
	#define VIRGIN_VERSION_V0_0_0_1		"Virgin version: V0.0.0.1"
	
	
	#if (VERSION_UPGRADE == YES)
        #define CURRENT_VERSION     "Version: V1.0.1     Build date: 2018-05-16"
		// #define CURRENT_VERSION		"Version: V0.01.1    Build date: 2012-07-27"
	#else
        #define PREVIOUS_VERSION    "Version: V0.01.1    Build date: 2012-07-27"
		// #define PREVIOUS_VERSION	""	
	#endif

#endif	/*    _VERSION_H    */

