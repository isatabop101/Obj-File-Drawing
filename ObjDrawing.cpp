#include<cstring>
#include<iostream>
#include<random>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
int vx[1000], vy[1000], vz[1000];
int vect[4][1000];
int vnsign[3][1000];
int vn[3][1000];
class FHDRaster {
  unsigned char data[1920][1080][3];
  public:
  FHDRaster(void) {
    memset(data, 0, 1920*1080*3);  
  }
  void
  setPixel(unsigned int x, unsigned int y, 
            unsigned char r, 
            unsigned char g, 
            unsigned char b) {
      if( x >= 1920 || y >= 1080) {
        return;
      }
      data[x][y][0] = r;
      data[x][y][1] = g;
      data[x][y][2] = b;
  }
  void
  write(void) {
   int x = 0;
   int y = 0;
   cout<<"P6\n1920 1080 255\n";
   for(y=0;y<1080;y++) {
     for(x=0;x<1920;x++) {
      cout<<data[x][y][0];
      cout<<data[x][y][1];
      cout<<data[x][y][2];
     } 
   }
  }
 void drawLine( 
  unsigned int x1, unsigned int y1, 
   unsigned int x2, unsigned int y2, 
    unsigned char r,
    unsigned char g,
    unsigned char b) {

      double m; //slope
      double be;
      double aux;
      unsigned int x = 0;
      unsigned int y = 0;
      int dx,dy,p,updateUp,updateRight;
        
      if(x2>x1 && y2>y1) { // signs check-in because x1,x2,y1,y2 are unsigned so can't be negative
      	 m = (double)(y2-y1)/(double)(x2-x1); 
      } 
      
      if(x1>x2 && y2>y1){
      	 m = (double)(y2-y1)/(double)(x1-x2);
      }
      
      if(x2>x1 && y1>y2){
      	 m = (double)(y1-y2)/(double)(x2-x1);
      }
      
      if(x1>x2 && y1>y2){
      	 m = (double)(y1-y2)/(double)(x1-x2);
      }
       if(x1==x2 || y1==y2){
      	 m = 0;
      }
      
      aux = m;
      
      if(x2>x1 && y2>y1 && aux<1 && aux>=0) { //1st Octant 
      	 m = (double)(y2-y1)/(double)(x2-x1); 
      	 be = (double)y1 - (m*x1); 
      	 dx = x2 - x1;
      	 dy = y2 - y1;  
      	 p = 2*dy-dx; 
      	 updateUp = 2*dy;      
      	 updateRight = 2*dy-2*dx;   
      } 
      
      if(x2>x1 && y2>y1 && aux>=1) { //2nd Octant
      	 m = (double)(y2-y1)/(double)(x2-x1); 
      	 be = (double)y1 - (m*x1); 
      	 dx = x2 - x1;
      	 dy = y2 - y1;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dx;          
      	 updateRight = 2*dx-2*dy; 
      }  
      
      if(x1>x2 && y2>y1 && aux>=1){ //3th octant
      	 m = (double)(x1-x2)/(double)(y2-y1);
      	 be = (double)x1 - (m*y1); 
      	 dx = x1 - x2;
      	 dy = y2 - y1;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dx;          
      	 updateRight = 2*dx-2*dy; 
      }
      
      if(x1>x2 && y2>y1 && aux<1 && aux>=0){ //4rd octant
      	 m = (double)(y2-y1)/(double)(x1-x2);
      	 be = (double)y1 - (m*x1); 
      	 dx = x1 - x2;
      	 dy = y2 - y1;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dy;          
      	 updateRight = 2*dy-2*dx; 
      }
      
      if(x2>x1 && y1>y2 && aux<1 && aux>=0){ //5th octant
      	 m = (double)(y1-y2)/(double)(x2-x1);
      	 be = (double)y1 - (m*x1); 
      	 dx = x2 - x1;
      	 dy = y1 - y2;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dy;          
      	 updateRight = 2*dy-2*dx; 
      }
       if(x2>x1 && y1>y2 && aux>=1){ //6th octant
      	 m = (double)(x2-x1)/(double)(y1-y2);
      	 be = (double)x1 - (m*y1);
      	 dx = x2 - x1;
      	 dy = y1 - y2;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dx;          
      	 updateRight = 2*dx-2*dy;  
      }
      
      if(x1>x2 && y1>y2 && aux>=1){ //7th Octant
      	 m = (double)(x1-x2)/(double)(y1-y2);
      	 be = (double)x1 - (m*y1);
      	 dx = x1 - x2;
      	 dy = y1 - y2;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dx;          
      	 updateRight = 2*dx-2*dy;  
      }
      
      if(x1>x2 && y1>y2 && aux<1 && aux>=0){ //8th Octant
      	 m = (double)(y1-y2)/(double)(x1-x2);
      	 be = (double)y1 - (m*x1);
      	 dx = x1 - x2;
      	 dy = y1 - y2;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dy;          
      	 updateRight = 2*dy-2*dx;  
      }
      if(y1==y2 && aux==0 ){
      	 m = 0;
      	 be = (double)x1 - (m*y1); 
      }
      
      if(x1==x2 && aux==0){
      	 m = 0;
      	 be = (double)y1 - (m*x1);
      }
         

      setPixel(x1, y1, r, g, b);
      setPixel(x2, y2, r, g, b);     
                                   
      
      if(x2>x1 && y2>y1 && aux>=0 && aux<1){    //1st Octant Drawing
      	 y = m*x1 + be;               
      	for( x = x1 + 1 ; x < x2 ; x++ ) {   
        	if( p < 0 ) { 
          		  y++;
          		  p+= updateUp; 
        	} else {
          		  p+= updateRight;
        	} 
        	setPixel(x, y, r, g, b); 
      		} 	
   	}
   	
   	if(x2>x1 && y2>y1 && aux>=1){    //2nd Octant drawing
      	 x = m*y1 - be;               
      	for( y = y1 + 1 ; y < y2 ; y++ ) {   
        	if( p < 0 ) { 
        		
          		p += updateUp;    
        	} else {
        		x++;
          		p += updateRight;
        	} 
        	setPixel(x, y, r, g, b); 
      		}  	
   	}
   	
       
       if(x1>x2 && y2>y1 && aux>=1) {    //3rd Octant drawing
         x = m*y1 + be;               
      	for( y = y1 + 1 ; y < y2 ; y++ ) {   
        	if( p < 0 ) { 
        		
          		p += updateUp;    
        	} else {
        		x--;
          		p += updateRight;
        	} 
        	setPixel(x, y, r, g, b); 
      		}  
   	}	
      
      
      if(x1>x2 && y2>y1 && aux>=0 && aux<1) {    //4th Octant drawing
         y = m*x1 + be; 
      	 for( x=x1-1 ; x>x2 ; x--) {
        	if( p < 0 ) { 
          		y++;
          		p += updateUp;    
        	} else {
          		p += updateRight;
        	} 
        	setPixel(x, y, r, g, b); 
      		} 
   	}	
       
       if(x2>x1 && y1>y2 && aux>=0 && aux<1) {    //5th octant drawing
       	y = m*x1 + be;
      		for( x=x1+1 ; x<x2 ; x++) {
        	 if( p < 0 ) { 
          		y--;
          		p += updateUp;    
        	 } else {
          		p += updateRight;
        	  } 
        	  setPixel(x, y, r, g, b); 
      			}	 
   		}	
      
      if(x2>x1 && y1>y2 && aux>=1) {    //6th octant drawing
       	x = m*y1 + be;               
      	 	for( y = y1-1; y>y2 ; y-- ) {   
        		if( p < 0 ) { 
          			p += updateUp;    
        		} else {
        			x++;
          			p += updateRight;
        		} 
        		setPixel(x, y, r, g, b); 
      		}	
      }
      
      if(x1>x2 && y1>y2 && aux>=1) {    //7th Octant Drawing
       	x = m*y1 + be;               
      	 	for( y = y1-1; y>y2 ; y-- ) {   
        		if( p < 0 ) { 
          			p += updateUp;    
        		} else {
        			x--;
          			p += updateRight;
        		} 
        		setPixel(x, y, r, g, b); 
      		}	
      }
      	
      if(x1>x2 && y1>y2 && aux>=0 && aux<1) {    //8th Octant drawing
       	y = m*x1 - be;
      		for( x=x1-1 ; x>x2 ; x--) {
        		if( p < 0 ) { 
          		y--;
          		p += updateUp;    
        	 } else {
          		p += updateRight;
        	  } 
        	  setPixel(x, y, r, g, b);
   		}	 
   	}
   	if(y1==y2 && aux==0) {    
       	x = m*y1 + be;
       	if(x1>x2){
      		for( x=x2+1 ; x<x1 ; x++) {
        	  setPixel(x, y1, r, g, b);
   		}
   		}
   		if(x2>x1){
      		for( x=x1+1 ; x<x2 ; x++) {
        	  setPixel(x, y1, r, g, b);
   		}
   		}	 
   	}
   	
   	if(x1==x2 && aux==0) {  
       	y = m*x1 + be;
       	if(y1>y2){
      		for( y=y2+1 ; y<y1 ; y++) {
        	  setPixel(x1, y, r, g, b);
   		}
   		}
   		if(y2>y1){
      		for( y=y1+1 ; y<y2 ; y++) {
         		  setPixel(x1, y, r, g, b);
   		}
   		}	 
   	 }	
   }
   
   int readObj(){
   	string line,line2;
   	string valuesX[1920], valuesY[1080], valuesZ[1920];
   	string vectS[4][1000];
   	string vnor[3][1000];
	string v,f,vnr;
	int n = 0;
	int m = 0;
	int o = 0;
	ifstream myfile ("monki.obj");
	while(!myfile.eof())
		{
    		getline (myfile,line);
    		if (line[0] == 'v' && line[1] != 't' && line[1] != 'n')
    			{	
    				std::istringstream iss( line );
				iss >> v >> valuesX[n] >> valuesY[n] >> valuesZ[n];
        			vx[n] = std::stoi (valuesX[n],nullptr,10);
        			vy[n] = std::stoi (valuesY[n],nullptr,10);
        			vz[n] = std::stoi (valuesZ[n],nullptr,10);
        			//cout << vx[n] << "\t" << vy[n] << "\t" << vz[n] << endl;
        			n++;
        			
    			}
    		if (line[0] == 'f')
    			{	
    				std::istringstream iss2( line );
				iss2 >> f >> vectS[0][m] >> vectS[1][m] >> vectS[2][m] >> vectS[3][m];
        			vect[0][m] = std::stoi (vectS[0][m],nullptr,10);
        			vect[1][m] = std::stoi (vectS[1][m],nullptr,10);
        			vect[2][m] = std::stoi (vectS[2][m],nullptr,10);
        			vect[3][m] = std::stoi (vectS[3][m],nullptr,10);
        			//cout << vect[0][m] << "\t" << vect[1][m] << "\t" << vect[2][m] << "\t" << vect[3][m] << endl;
        			m++;
    			}
    		 if (line[0] == 'v' && line[1] == 'n' && line[1] != 't'){
    		 		std::istringstream iss2( line );
				iss2 >> vnr >> vnor[0][o] >> vnor[1][o] >> vnor[2][o];
        			vnsign[0][o] = std::stoi (vnor[0][o],nullptr,10);
        			vnsign[1][o] = std::stoi (vnor[1][o],nullptr,10);
        			vnsign[2][o] = std::stoi (vnor[2][o],nullptr,10);
        			vn[0][o] = std::stoi (vnor[0][o],nullptr,10);
        			vn[1][o] = std::stoi (vnor[1][o],nullptr,10);
        			vn[2][o] = std::stoi (vnor[2][o],nullptr,10);
        			
        			if(vn[0][o]<0){
 					vn[0][o] = vn[0][o]*-1;
 				}
 				
 				if(vn[1][o]<0){
 					vn[1][o] = vn[1][o]*-1;
 				}
 				
 				if(vn[2][o]<0){
 					vn[2][o] = vn[2][o]*-1;
 				}
        			
        			//cout << vnsign[0][o] << "\t" << vnsign[1][o] << "\t" << vnsign[2][o] << endl;
        			o++;
    		 	}	
    		}
    	
    			  		
    	  return m;	  
     	}
     
     void checkValues(){
        int lenghtX = sizeof(vx);
        int lenghtY = sizeof(vy);
        int lenghtZ = sizeof(vz);
        
     	for(int i = 0; i<lenghtX; i++){
     		if(vx[i] < 0){
     			vx[i] = vx[i] * -2;
     		}
     	 }
     	 
     	 for(int m = 0; m<lenghtY; m++){
     		if(vy[m] < 0){
     			vy[m] = vy[m] * -2;
     		}
     	 }
     	 for(int n = 0; n<lenghtZ; n++){
     		if(vz[n] < 0){
     			vz[n] = vz[n] * -2;
     		}
     	 }
     	 
     	}
     	
     	
};

/* testing */
int main(void) {
 FHDRaster * raster = new FHDRaster();
 unsigned int x = 0;
 unsigned int y = 0;
 unsigned char r = 0x00;
 unsigned char g = 0x00;
 unsigned char b = 0x00;
 int n = 0;
 int contador;
 int auX[1000];
 int auY[1000];
 int auZ[1000];
 n = raster -> readObj();
 raster -> checkValues();
 //cout<<n<<"\n";

 for(int i = 0; i<n; i++){
 	
 		if(vn[2][i] > vn[0][i] && vn[2][i] > vn[1][i]){
 			
 			if(vnsign[2][i]>0){
 			
 				raster->drawLine(vx[vect[0][i]-1], vy[vect[0][i]-1], vx[vect[1][i]-1], vy[vect[1][i]-1], 255, 255, 255);	
 				raster->drawLine(vx[vect[1][i]-1], vy[vect[1][i]-1], vx[vect[2][i]-1], vy[vect[2][i]-1], 255, 255, 255);
 				raster->drawLine(vx[vect[2][i]-1], vy[vect[2][i]-1], vx[vect[3][i]-1], vy[vect[3][i]-1], 255, 255, 255);
 				raster->drawLine(vx[vect[3][i]-1], vy[vect[3][i]-1], vx[vect[0][i]-1], vy[vect[0][i]-1], 255, 255, 255);
 			}
 			
 			if(vnsign[2][i]<0){
 			
 				for(int e = 0; e<4 ; e++){
 					auX[e] = vx[vect[e][i]-1] - vz[vect[e][i]-1];
 					auY[e] = vy[vect[e][i]-1] - vz[vect[e][i]-1];
 					if(auX[e]<0){
 						auX[e] = auX[e]*-1;
 					}
 					if(auY[e]<0){
 						auY[e] = auY[e]*-1;
 					}
 				}
 				raster->drawLine(auX[0], auY[0], auX[1], auY[1], 255, 255, 255);	
 				raster->drawLine(auX[1], auY[1], auX[2], auY[2], 255, 255, 255);
 				raster->drawLine(auX[2], auY[2], auX[3], auY[3], 255, 255, 255);
 				raster->drawLine(auX[3], auY[3], auX[0], auY[0], 255, 255, 255);
 			}
 		}
 		
 		
 		if(vn[1][i] > vn[2][i] && vn[1][i] > vn[0][i]){
 			
 			if(vnsign[1][i]>0){
 				for(int e = 0; e<4 ; e++){
 					auX[e] = vx[vect[e][i]-1] - vy[vect[e][i]-1];
 					auZ[e] = vz[vect[e][i]-1] - vy[vect[e][i]-1];
 					if(auX[e]<0){
 						auX[e] = auX[e]*-1;
 					}
 					if(auZ[e]<0){
 						auZ[e] = auZ[e]*-1;
 					}
 				}
 				
 				raster->drawLine(vx[vect[0][i]-1], auZ[0], auX[1], vz[vect[1][i]-1], 255, 255, 255);	
 				raster->drawLine(auX[1], vz[vect[1][i]-1], auZ[2], auX[2], 255, 255, 255);
 				raster->drawLine(auZ[2], auX[2], auX[3], auZ[3], 255, 255, 255);
 				raster->drawLine(auX[3], auZ[3], vx[vect[0][i]-1], auZ[0], 255, 255, 255);
 				
 				}
 			
 			
 			if(vnsign[1][i]<0){
 			
 				for(int e = 0; e<4 ; e++){
 					auX[e] = vx[vect[e][i]-1] - vy[vect[e][i]-1];
 					auZ[e] = vz[vect[e][i]-1] - vy[vect[e][i]-1];
 					if(auX[e]<0){
 						auX[e] = auX[e]*-1;
 					}
 					if(auZ[e]<0){
 						auZ[e] = auZ[e]*-1;
 					}
 				}
 				raster->drawLine(vx[vect[3][i]-1], vz[vect[3][i]-1], vx[vect[1][i]-1], auZ[1], 255, 255, 255);
 				raster->drawLine(vx[vect[1][i]-1],auZ[1], vx[vect[2][i]-1], vz[vect[2][i]-1], 255, 255, 255);
 				raster->drawLine(vx[vect[2][i]-1], vz[vect[2][i]-1],vx[vect[0][i]-1], vz[vect[0][i]-1], 255, 255, 255);
 				raster->drawLine(vx[vect[0][i]-1], vz[vect[0][i]-1],vx[vect[3][i]-1], vz[vect[3][i]-1], 255, 255, 255);
 			}
 			}
 			
 			if(vn[0][i] > vn[2][i] && vn[0][i] > vn[1][i]){
 			
 			if(vnsign[0][i]>0){
 				for(int e = 0; e<4 ; e++){
 					auY[e] = vy[vect[e][i]-1] - vx[vect[e][i]-1];
 					auZ[e] = vz[vect[e][i]-1] - vx[vect[e][i]-1];
 					if(auY[e]<0){
 						auY[e] = auY[e]*-1;
 					}
 					if(auZ[e]<0){
 						auZ[e] = auZ[e]*-1;
 					}
 				}
 				
 				raster->drawLine(vy[vect[0][i]-1], vz[vect[0][i]-1], vy[vect[1][i]-1], vz[vect[1][i]-1], 255, 255, 255);	
 				raster->drawLine(vy[vect[1][i]-1], vz[vect[1][i]-1], auY[2], vz[vect[2][i]-1], 255, 255, 255);
 				raster->drawLine(auY[2], vz[vect[2][i]-1], auY[3], vz[vect[3][i]-1], 255, 255, 255);
 				raster->drawLine(auY[3], vz[vect[3][i]-1], vy[vect[0][i]-1], vz[vect[0][i]-1], 255, 255, 255);
 				
 				}
 			
 			
 			if(vnsign[0][i]<0){
 			
 				for(int e = 0; e<4 ; e++){
 					auY[e] = vy[vect[e][i]-1] - vx[vect[e][i]-1];
 					auZ[e] = vz[vect[e][i]-1] - vx[vect[e][i]-1];
 					if(auY[e]<0){
 						auY[e] = auY[e]*-1;
 					}
 					if(auZ[e]<0){
 						auZ[e] = auZ[e]*-1;
 					}
 				}
 				raster->drawLine(vy[vect[0][i]-1], vz[vect[0][i]-1], vy[vect[1][i]-1], vz[vect[1][i]-1], 255, 255, 255);	
 				raster->drawLine(vy[vect[1][i]-1], vz[vect[1][i]-1], auY[3], auZ[3], 255, 255, 255);
 				raster->drawLine(auY[3], auZ[3],vy[vect[2][i]-1],auZ[2], 255, 255, 255);
 				raster->drawLine(vy[vect[2][i]-1], auZ[2], vy[vect[0][i]-1], vz[vect[0][i]-1], 255, 255, 255);
 			}
 			
 		}
 		}
	
 raster->write();

 return 0;
}
