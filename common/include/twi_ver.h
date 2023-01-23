/*-**************************************************************************-*/ 
/*- @file      twi_ver.h header file                                          */ 
/*- Copyright 2020 Thirdwayv Inc - All Rights Reserved.                       */ 
/*- Unauthorized copying of this file or portions thereof,                    */ 
/*- via any medium, is strictly prohibited.                                   */ 
/*- Proprietary and confidential.                                             */ 
/*-**************************************************************************-*/ 
  
#ifndef TWI_VER_H_ 
#define TWI_VER_H_ 
  
#define GIT_SDK_VER "8fa5944" 
  
#define GIT_SDK_BRANCH "master" 
  
#define GIT_APP_VER "7418378" 
  
#define GIT_APP_BRANCH "ALGN-99" 
  
#define GIT_REQ_SDK_BRANCH "master" 
  
#define GIT_VER_SIZE 7 
  
#define GIT_REQ_SDK_VER "8fa5944" 
  
#define GIT_SDK_VER_VALID 1 
  
#define GIT_SDK_BRANCH_VALID 1 
  
#if (GIT_SDK_BRANCH_VALID == 0) 
#error "Not valid Platform SDK branch review SDK_NAME in eclipse make file or keil preBuild.bat script Argument 1" 
#endif 
  
#if (GIT_SDK_VER_VALID == 0) 
#error "Not valid Platform SDK version review SDK_VER in eclipse make file or keil preBuild.bat script Argument 2" 
#endif 
  
#endif /* TWI_VER_H_ */ 
