// Program:     photoshop_bouns.cpp
// Purpose:     Demonstrate use of bmplip for handling
//              bmp colored images

/* Authors:   Badr Nasr Al-Din Al-Badri    id->20210086

*/
// Date:    9 April 2022
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
// ___________________________________________
// variables
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char newimage[SIZE][SIZE][RGB];
unsigned char ShuffleImage[4][SIZE][SIZE][RGB];
unsigned char temp[SIZE][SIZE][RGB];
unsigned char temp2[SIZE][SIZE/2][RGB];
// ___________________________________________
// Functions
void loadImage ();
void load_img2();
void saveImage ();
void save_img2();

void Black_White();
void Invert_Filter ();
void merge();
void flip_image();
void darken_lighten();
void Rotate_Image();
void detect();
void Enlarge_Image();
void shrink();
void Shuffle_Image();
void mirror_image();
void blur_image();
void crop_image();
void skew_image();

// ______________________________________________________________________________________________________________________________________
int main()
{
  
    // choose from filters
    int num;
    cout<<"Ahlan ya user ya habibi\n";
    cout<<"1->Black_White\n2->Invert_Filter\n3->merge_filter\n4->flip_image\n5->darken&lighten\n6->Rotate_Image\n7->detect";
    cout<<"\n8->Enlarge_Image\n9->shrink\n10->mirror_image\n11->Shuffle_Image\n12->blur_filter\n13->blur_filter\n14->skew_filter\n0->Exit\n";
    cout<<"please choose the filter you want : ";
    cin>>num;
    if(num==1){
        loadImage ();
        Black_White();
        saveImage ();
    }
    else if(num==2){
        loadImage ();
        Invert_Filter();
        saveImage ();
    }
    else if(num==3){
        loadImage ();
        load_img2();
        merge();
        save_img2();
    }
    else if(num==4){
        loadImage ();
        flip_image();
        saveImage ();
    }
    else if(num==5){
        loadImage ();
        darken_lighten();
        save_img2();
    }
    else if(num==6){
        loadImage ();
        Rotate_Image();
        saveImage ();
    }
    else if(num==7){
        loadImage ();
        detect();
        saveImage ();
    }
    else if(num==8){
        loadImage ();
        Enlarge_Image();
        saveImage ();
    }
    else if(num==9){
        loadImage ();
        shrink();
        save_img2();
    }
    else if(num==10){
        loadImage ();
        mirror_image();
        saveImage ();
    }
    else if(num==11){
        loadImage ();
        Shuffle_Image();
        saveImage ();
    }
    else if(num==12){
        loadImage ();
        blur_image();
        save_img2();
    }
    else if(num==13){
        loadImage ();
        crop_image();
        save_img2();
    }
    else if(num==0){
        cout<<"Thanks for using photoshop";
    }
    

  
  return 0;
}
// ______________________________________________________________________________________________________________________________________
void loadImage () {
   char imageFileName[100];

   // Get colord image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readRGBBMP(imageFileName, image);
}
// ______________________________________________________________________________________________________________________________________

/*load the image you want to merge in the (merge) function*/
void load_img2()
{
    char imgfilename[100];
    cout << "Please enter the name of BMP tp merge with: ";
    cin >> imgfilename;
    strcat(imgfilename, ".bmp");
    readRGBBMP(imgfilename, image2);

}
// ______________________________________________________________________________________________________________________________________

void saveImage () {
   char imageFileName[100];

   // Get colored scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, image);
}
// ______________________________________________________________________________________________________________________________________

void save_img2()
{
    char imgfilename[100];
    cout << "Enter target image file name: ";
    cin >> imgfilename;
    strcat(imgfilename, ".bmp");
    writeRGBBMP(imgfilename, newimage);
}
// ______________________________________________________________________________________________________________________________________

void Black_White() {

  cout << "Black_White image\n************************"<<endl<<endl;
  // nested loop for array three D
   for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int d= 0; d< RGB; d++){
                // calc the average
                int average = ((image[i][j][0])+(image[i][j][1])+(image[i][j][2]))/3;

                image[i][j][0] = average;
                image[i][j][1] = average;
                image[i][j][2] = average;
            }
        }
    }
    // convert gray photo to black & whitte
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int d = 0; d< RGB; d++){
                if (image[i][j][d] > 128) {
                    image[i][j][d] = 255;
                }
                else {
                    image[i][j][d] = 0;
                }
            }
        }
    }
}
// ______________________________________________________________________________________________________________________________________

void Invert_Filter (){
    for(int d=0;d<RGB;d++){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
             // if the pixel is white we turn it into black
                if (image[i][j][d] ==255)
                    image[i][j][d] = 0;
             // if the pixel is black we turn it into white  
                else if(image[i][j][d] ==0)
                    image[i][j][d] = 255;
             // if not black or white we sub from 255 
                else
                    image[i][j][d]= 255-image[i][j][d];      
            }
        }
            
    }
}
// _____________________________________________________________________________________________________________________________________

void merge() {
   
    for(int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            for(int d=0;d<RGB;d++){ 
                newimage[i][j][d]=(image[i][j][d] + image2[i][j][d])/2;
            }
        }
    }
}
// _____________________________________________________________________________________________________________________________________

void flip_image(){
   cout<<"we do horizon or vertical flip image\n*************************************\n\n";
   cout<<"choice 1 for horizon image\nAny other choice for vertical image\n\n";
   cout<<"Enter your choice : ";

   int c;

   cin>>c;
   cout<<endl;
   //nested loop for array two D 
   if (c==1){
      // this loop for rows 
      //size/2 because we edit rows 
        for(int d=0;d<RGB;d++){  
            for (int i=0 ;i<SIZE/2; i++){
                for (int j=0; j<SIZE;j++){
                    temp[i][j][d]=image[i][j][d];
                    image[i][j][d]=image[255-i][j][d];
                    image[255-i][j][d]=temp[i][j][d];//make array image = edit array (temp)
                }
            }
        }
   }
   else {
        // this loop for column 
        //size/2 because we edit column
        for(int d=0;d<RGB;d++){  
            for (int i=0 ;i<SIZE; i++){
                for (int j=0; j<SIZE/2;j++){
                    temp2[i][j][d]=image[i][255-j][d];
                    image[i][255-j][d]=image[i][j][d];
                    image[i][j][d]=temp2[i][j][d];  //make array image = edit array (temp2)
                }
            }
        }
   }
}
// ______________________________________________________________________________________________________________________________________
void Rotate_Image(){
   int x;
   cout<<"1-> rotate 90\n2-> rotate 180\n3-> rotate 270\nplease enter num of rotate:";
   cin>>x;
  //  loop on every pixel in image.
  for(int d=0;d<RGB;d++){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
        //  Here we transpose every pixel. 
            // Rotate 90 .
            if(x==1) {
                newimage[j][255-i][d]= image[i][j][d] ; 
            }
            // Rotate 180.
            else if(x==2) {
                newimage[255-i][j][d]= image[i][j][d] ;
            }
            // Rotate 270 .
            else if(x==3) {
                newimage[255-j][i][d]= image[i][j][d] ;

            }
        }    
    
    }
  }
  // Save image in varible image.
    for(int d=0;d<RGB;d++){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
            image[i][j][d]=newimage[i][j][d];
            }
        }
    }
}
// ______________________________________________________________________________________________________________________________________

// a function to darken or lighten a given picture
void darken_lighten() {
    int decision;
    // make the user choose
    cout << "To darken please enter 1\nTo lighten please enter 2\nEnter: ";
    cin >> decision;
    if (decision == 1) {
        // loop through all the pixels
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int d=0;d<RGB;d++){
                    //get all the surrounding pixels and multiply by 0.025
                    newimage[i][j][d] =(image[i + 1][j + 1][d] * 0.025 + image[i][j + 1][d] * 0.025 + image[i + 1][j][d] * 0.025 +
                                        image[i - 1][j - 1][d] * 0.025 + image[i][j - 1][d] * 0.025 + image[i - 1][j][d] * 0.025 +
                                        image[i - 1][j + 1][d] * 0.025 + image[i+1][j-1][d] * 0.025 + image[i][j][d] * 0.025 / 9);
                    }
            }
        }
    }

    else if (decision == 2) {
        // loop through all the pixels
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int d=0;d<RGB;d++){
                    //add 255 to the initial pixels then divide by 2 to inc. the brightness
                    newimage[i][j][d] = (image[i][j][d]+255)/2 ;
                }
            }
        }
    }
}
// ______________________________________________________________________________________________________________________________________

void detect(){
    cout<<"detect edges for image\n*****************************\n\n";
    bool temp[SIZE][SIZE][RGB];
    //make image black and white
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int d = 0; d<RGB; d++) {

                if (image[i][j][d] > 127)
                    image[i][j][d] = 255;
                else
                    image[i][j][d] = 0;
            }      
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int d = 0; d<RGB; d++) {
                    temp[i][j][d]=image[i][j][d];
                    //check that index [i][j] that the index before it and after is black
                if (image [i][j+1][d]==0 && image[i][j-1][d]==0 && image[i+1][j][d]==0 && image[i-1][j][d]==0 
                    && image[i+1][j+1][d]==0 && image[i+1][j-1][d]==0 && image[i-1][j+1][d]==0 && image[i-1][j-1][d]==0){

                    temp[i][j][d]=true;//if if condition is true dont edit this index
                    }        
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int d = 0; d<RGB; d++) {
                if (temp[i][j][d]==1){
                    image[i][j][d]=255;
                }
            }
        }
    }
}
// ______________________________________________________________________________________________________________________________________

void Enlarge_Image(){
   int x=0,y=0,z;
   cout<<"1->top left side\n2->top right side\n3->down left side\n4->down right side";
   cout<<"\nplease choose the num of the side you want :  ";
   cin>>z;
    // top left side 
    if(z==1){
        // loop on the top left side of image
        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 0; j< SIZE/2; j++) {
                for(int d=0;d<RGB;d++){
                    // her we repeat every pixel 4 times
                    newimage[x][y][d]=image[i][j][d];

                    newimage[x][y+1][d]=image[i][j][d];

                    newimage[x+1][y+1][d]=image[i][j][d];

                    newimage[x+1][y][d]=image[i][j][d];
                }
                y+=2;
            }
            x+=2;
            y=0;
        }
    }
    //  top right side 
    else if(z==2){ 
        // loop on the top right side of image
        for (int i = 0; i < SIZE/2; i++) {
            for (int j = 128; j< SIZE; j++) {
                for(int d=0;d<RGB;d++){
                    // her we repeat every pixel 4 times
                    newimage[x][y][d]=image[i][j][d];

                    newimage[x][y+1][d]=image[i][j][d];

                    newimage[x+1][y+1][d]=image[i][j][d];

                    newimage[x+1][y][d]=image[i][j][d];
                }
                y+=2;
            }
                x+=2;
                y=0;
        }
    }

    // down left side
    else if(z==3){
        // loop on the down left side of image
        for (int i = 128; i < SIZE; i++) {
            for (int j = 0; j< SIZE/2; j++) {
                for(int d=0;d<RGB;d++){
                    // her we repeat every pixel 4 times
                    newimage[x][y][d]=image[i][j][d];

                    newimage[x][y+1][d]=image[i][j][d];

                    newimage[x+1][y+1][d]=image[i][j][d];

                    newimage[x+1][y][d]=image[i][j][d];
                }
                y+=2;
            }
                x+=2;
                y=0;
        }
        
    }
    // down right side
    else if(z==4){
        // loop on the down right side of image
        for (int i = 128; i < SIZE; i++) {
            for (int j = 128; j< SIZE; j++) {
                for(int d=0;d<RGB;d++){
                    // her we repeat every pixel 4 times
                    newimage[x][y][d]=image[i][j][d];

                    newimage[x][y+1][d]=image[i][j][d];

                    newimage[x+1][y+1][d]=image[i][j][d];

                    newimage[x+1][y][d]=image[i][j][d];
                }
                y+=2;
            }
                x+=2;
                y=0;
        }
    }
    // save newimage in image
    for(int d=0;d<RGB;d++){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image[i][j][d]=newimage[i][j][d];
            }
        }
    }
}
// ______________________________________________________________________________________________________________________________________

void shrink ()
{
    // declare int shrinkage k,L 
   int shrinkage,k=0,l=0;
   // ask user for input on degree of shrinkage
   cout << "1-shrink to 1/2 \n2-shrink to 1/3\n3-shrink to 1/4 \nenter your choice: ";
   cin >> shrinkage;
   if (shrinkage == 1)
   {
       //loop through all the pixels , while skipping a pixel each time
        for(int i=0; i<SIZE; i+=2) {
            for (int j = 0; j < SIZE; j+=2) {
                for(int d=0;d<RGB;d++){
                    newimage[k][l][d] = image[i][j][d];
                }    
                l++;
            }
            l=0;
            k++;
        }
       
   }
   else if (shrinkage == 2)
   {
       //loop through all the pixels , while skipping a pixel each time
      for(int i=0; i<SIZE; i+=3) {
         for (int j = 0; j < SIZE; j+=3) {
            for(int d=0;d<RGB;d++){
                newimage[k][l][d] = image[i][j][d];
            }
            l++;
         }
         l=0;
         k++;
      }

   }
   else if (shrinkage == 3)
   {
       //loop through all the pixels , while skipping a pixel each time
      for(int i=0; i<SIZE; i+=4) {
         for (int j = 0; j < SIZE; j+=4) {
            for(int d=0;d<RGB;d++){
                newimage[k][l][d] = image[i][j][d];
            }
            l++;
         }
         l=0;
         k++;
      }
   }
}
// ______________________________________________________________________________________________________________________________________

void Shuffle_Image(){
   int a,b,c,d,x=0,y=0;
   cout<<"please enter the arrange of photos :";
   cin>>a>>b>>c>>d;
      // top left side 
    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 0; j< SIZE/2; j++) {
            for(int k=0;k<RGB;k++){
                // assign part 1 to top left side 
                ShuffleImage[0][x][y][k]=image[i][j][k];
            }
            y+=1;
        }
        y=0;
        x+=1;
    }
    x=0;
      // top right side 
    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 128; j< SIZE; j++) {
            for(int k=0;k<RGB;k++){
                // assign part 2 to top right side
                ShuffleImage[1][x][y][k]=image[i][j][k];
            }
            y+=1;
        }
        y=0;
        x+=1;
    }
    x=0;
        // down left side
    for (int i = 128; i < SIZE; i++) {
        for (int j = 0; j< SIZE/2; j++) {
            for(int k=0;k<RGB;k++){
                // assign part 4 to down left side
                ShuffleImage[2][x][y][k]=image[i][j][k];
            }
            y+=1;
        }
        y=0;
        x+=1;
    } 
    x=0;
      // down right side

    for (int i = 128; i < SIZE; i++) {
        for (int j = 128; j< SIZE; j++) {
            for(int k=0;k<RGB;k++){
                // assign part 4 to down right side
                ShuffleImage[3][x][y][k]=image[i][j][k];
            }
            y+=1;
        }
        y=0;
        x+=1;
    }
    x=0;

    // save ShuffleImage in image ( top left side )  
    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 0; j< SIZE/2; j++) {
            for(int k=0;k<RGB;k++){
                image[i][j][k]=ShuffleImage[a-1][x][y][k];
            }
            y+=1;
        }
        y=0;
        x+=1;
    }
    x=0;
    // save ShuffleImage in image ( top right side ) 
    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 128; j< SIZE; j++) {
            for(int k=0;k<RGB;k++){
                image[i][j][k]=ShuffleImage[b-1][x][y][k];
            }
            y+=1;
        }
        y=0;
        x+=1;
    }
    x=0;
    // save ShuffleImage in image (down left side)
    for (int i = 128; i < SIZE; i++) {
        for (int j = 0; j< SIZE/2; j++) {
            for(int k=0;k<RGB;k++){
                image[i][j][k]=ShuffleImage[c-1][x][y][k];
            }
            y+=1;
        }
        y=0;
        x+=1;
    }
    x=0;
    // save ShuffleImage in image (down right side)
    for (int i = 128; i < SIZE; i++) {
        for (int j = 128; j< SIZE; j++) {
            for(int k=0;k<RGB;k++){
                image[i][j][k]=ShuffleImage[d-1][x][y][k];
            }
            y+=1;
        }
        y=0;
        x+=1;
    }
    x=0;

}
// ______________________________________________________________________________________________________________________________________

void mirror_image(){
  int x;
  cout <<"1-if you want 1/2 right\n2-if you want 1/2 left\n3-if you want 1/2 lower\n4-if you want 1/2 upper\n\n ";
  cout<<"Enter your choice : ";
  cin >> x;
    if (x == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                //size - j to flip column
                for (int d = 0; d<RGB; d++) {

                    image[i][j][d]= image[i][SIZE-j][d];
                }    
            }
        }
    }
    if (x == 2){
        for (int i = 0; i < SIZE; i++) {
            //size/2 to loop from middle index to the end
            for (int j = SIZE/2; j < SIZE; j++) {
                    for (int d = 0; d<RGB; d++) {
                        image[i][j][d] = image[i][SIZE-j][d];
                    }    
                }
            }
    }
    if (x == 3){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                    //size-1-i to flip rows
                for (int d = 0; d<RGB; d++) {

                    image[i][j][d] = image[SIZE-1-i][j][d];
                }   
            }
        }
    }
    if (x == 4){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                //make filp image = image
                for (int d = 0; d<RGB; d++) {
                    image[SIZE-1-i][j][d]= image[i][j][d];
                } 
            }
        }
    }
}
// ______________________________________________________________________________________________________________________________________
/*function that blurs the loaded image and saves it*/
void blur_image()
{
    for(int i=0; i<SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int d = 0; d<RGB; d++) { 
                newimage[i][j][d] = (image[i+1][j+1][d]*0.12 + image[i][j+1][d]*0.12 + 
                image[i+1][j][d]*0.12 + image[i-1][j-1][d]*0.12 + image[i][j-1][d]*0.12 + 
                image[i-1][j][d]*0.12 + image[i-1][j+1][d]*0.12 + image[i+1][j-1][d]*0.120 + image[i][j][d]*0.120/9);
            }
        }
    }
}

