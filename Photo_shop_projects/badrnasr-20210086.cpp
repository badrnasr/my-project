// Program:    photoshop.cpp
// Purpose:    Demonstrate use of bmplip for handling
//             bmp grayscale images

/* Authors:  Badr Nasr Al-Deen Al-Badri    id->20210086
             
*/
// Date:    17 April 2022
// Version: 1.1
// _________________________________
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
//___________________________________
// variables
unsigned char image[SIZE][SIZE];
unsigned char newimage[SIZE][SIZE];
unsigned char temp[SIZE][SIZE];
unsigned char temp2[SIZE][SIZE/2];
unsigned char image2 [SIZE][SIZE];
unsigned char ShuffleImage[4][128][128];
// __________________________________
// Functions
void loadImage ();
void load_img2();
void load_img();

void saveImage ();
void save_img2();

void Black_White();
void Invert_Filter ();
void flip_image(); 
void darken_lighten();
void Rotate_Image();
void detect();
void Enlarge_Image();
void shrink ();
void mirror_image();
void Shuffle_Image();
void blur();
void merge();
void crop();
void skew();
// ____________________________________


int main()
{

      // choose from filters
      int num;
      cout<<"Ahlan ya user ya habibi\n";
      cout<<"1->Black_White\n2->Invert_Filter\n3->merge_filter\n4->flip_image\n5->darken_lighten\n6->Rotate_Image";
      cout<<"\n7->detect\n8->Enlarge_Imagen\n9->shrink\n10->mirror_image\n11->Shuffle_Image\n12->blur_filter\n13->crop_filter\n14->skew_image\n0->Exit\n";
      cout<<"please choose the filter you want :  ";
      cin>>num;
      if(num==1){
            loadImage();
            Black_White();
            saveImage();
      }
      else if(num==2){
            loadImage();
            Invert_Filter ();
            saveImage();
      }
      else if(num==3){
            load_img();
            load_img2();
            merge();
            save_img2();
      }
      else if(num==4){
            loadImage();
            flip_image();
            saveImage(); 
      }
      else if(num==5){
            loadImage();
            darken_lighten();
            save_img2();
      }
      else if(num==6){
            loadImage();
            Rotate_Image();
            save_img2();
      }  
      else if(num==7){
            loadImage();
            detect();
            saveImage();
      }  
      else if(num==8){
            loadImage();
            Enlarge_Image();
            saveImage();
      }  
      else if(num==9){
            loadImage();
            shrink ();
            save_img2();
      }  
      else if(num==10){
            loadImage();
            mirror_image();
            saveImage();
      }  
      else if(num==11){
            loadImage();
            Shuffle_Image();
            saveImage();
      }  
      else if(num==12){
            load_img();
            blur();
            save_img2();
            
      }
      else if(num==13){
            loadImage();
            crop();
            save_img2();
      }  
      else if(num==0){
         cout<<"Thank you for using photoshop";
      }
   return 0;
}
// ______________________________________________________________________________________________________________________________________

/*load the original image*/
void load_img()
{
    char imgfilename[100];
    cout << "Enter the image file name: ";
    cin >> imgfilename;
    strcat(imgfilename, ".bmp");
    readGSBMP(imgfilename, image);

}
// ______________________________________________________________________________________________________________________________________

/*load the image you want to merge in the (merge) function*/
void load_img2()
{
    char imgfilename[100];
    cout << "Please enter the name of BMP tp merge with: ";
    cin >> imgfilename;
    strcat(imgfilename, ".bmp");
    readGSBMP(imgfilename, image2);

}
// ______________________________________________________________________________________________________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

// ______________________________________________________________________________________________________________________________________

void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}
// ______________________________________________________________________________________________________________________________________

/*save in file the edited image*/
void save_img2()
{
    char imgfilename[100];
    cout << "Enter target image file name: ";
    cin >> imgfilename;
    strcat(imgfilename, ".bmp");
    writeGSBMP(imgfilename, newimage);
}
// ______________________________________________________________________________________________________________________________________

void Black_White() {
   cout << "We do Black_White image\n************************"<<endl<<endl;
   // nested loop for array two D
   for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j< SIZE; j++) {

         if (image[i][j] > 127)
               image[i][j] = 255;// make pixel white 
         else
               image[i][j] = 0;//make pixel black

      }
   }
}
// ______________________________________________________________________________________________________________________________________

void Invert_Filter (){
      for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j< SIZE; j++) {

            // if the pixel is white we turn it into black
            if (image[i][j] ==255)
               image[i][j] = 0;
            // if the pixel is black we turn it into white         
            else if(image[i][j] ==0)
               image[i][j] = 255;
            // if not black or white we sub from 255  
            else
               image[i][j]= 255-image[i][j];      
         }
      }
}
// ______________________________________________________________________________________________________________________________________

/*function that makes you choose 2 pictures to merge together and saves it*/
void merge() {

   for(int i=0; i<SIZE; i++){
      for (int j=0; j<SIZE; j++){
         newimage[i][j]=(image[i][j] + image2[i][j])/2;
      }
   }

}
// ______________________________________________________________________________________________________________________________________

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
      for (int i=0 ;i<SIZE/2; i++){
         for (int j=0; j<SIZE;j++){ 
            temp[i][j]=image[i][j];
            image[i][j]=image[255-i][j];
            image[255-i][j]=temp[i][j];//make array image = edit array (temp)
         }
      }
   }
   else {
      // this loop for column 
      //size/2 because we edit column
      for (int i=0 ;i<SIZE; i++){
         for (int j=0; j<SIZE/2;j++){
            temp2[i][j]=image[i][255-j];
            image[i][255-j]=image[i][j];
            image[i][j]=temp2[i][j];//make array image = edit array (temp2)
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
            //get all the surrounding pixels and multiply by 0.025
            newimage[i][j] = (image[i + 1][j + 1] * 0.025 + image[i][j + 1] * 0.025 + image[i + 1][j] * 0.025 +
                              image[i - 1][j - 1] * 0.025 + image[i][j - 1] * 0.025 + image[i - 1][j] * 0.025 +
                              image[i - 1][j + 1] * 0.025 + image[i + 1][j - 1] * 0.025 + image[i][j] * 0.025 / 9);
         }
      }
   }

   else if (decision == 2) {
      // loop through all the pixels
      for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
               //add 255 to the initial pixels then divide by 2 to inc. the brightness
               newimage[i][j] = (image[i][j]+255)/2 ;
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
   for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j< SIZE; j++) {
         //  Here we transpose every pixel. 
         // Rotate 90 .
         if(x==1) {
            newimage[j][255-i]= image[i][j] ; 
         }
         // Rotate 180.
         else if(x==2) {
            newimage[255-i][j]= image[i][j] ;
         }
         // Rotate 270 .
         else if(x==3) {
            newimage[255-j][i]= image[i][j] ;

         }
      }
      
   }

}
// ______________________________________________________________________________________________________________________________________\

void detect(){
   cout<<"detect edges for image\n*****************************\n\n";
   bool temp[SIZE][SIZE];
   //make image black and white
   for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j< SIZE; j++) {

         if (image[i][j] > 127)
               image[i][j] = 255;
         else
               image[i][j] = 0;
      }
   }
   for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j< SIZE; j++) {
               temp[i][j]=image[i][j];
               //check that index [i][j] that the index before it and after is black
         if (image [i][j+1]==0 && image[i][j-1]==0 && image[i+1][j]==0 && image[i-1][j]==0 
         && image[i+1][j+1]==0 && image[i+1][j-1]==0 && image[i-1][j+1]==0 && image[i-1][j-1]==0){
                  temp[i][j]=true;//if if condition is true dont edit this index
         }
      }
   }
   for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j< SIZE; j++) {
               if (temp[i][j]==1){
                  image[i][j]=255;
         }
      }
   }
}
// ______________________________________________________________________________________________________________________________________

void Enlarge_Image(){
   int x=0,y=0,z;
   cout<<"1->top left side\n2->down left side\n3->top right side\n4->down right side";
   cout<<"\nplease choose the num of the side you want :";
   cin>>z;
   // top left side 
   if(z==1){
      // loop on the top left side of image
      for (int i = 0; i < SIZE/2; i++) {
         for (int j = 0; j< SIZE/2; j++) {
            // her we repeat every pixel 4 times
            newimage[x][y]=image[i][j];

            newimage[x] [y+1]=image[i][j];

            newimage[x+1] [y+1]=image[i][j];

            newimage[x+1] [y]=image[i][j];
            y+=2;
         }
         x+=2;
         y=0;
      }
   }
// down left side
   else if(z==2){
      // loop on the down left side of image
      for (int i = 128; i < SIZE; i++) {
         for (int j = 0; j< SIZE/2; j++) {
            // her we repeat every pixel 4 times
            newimage[x][y]=image[i][j];

            newimage[x] [y+1]=image[i][j];

            newimage[x+1] [y+1]=image[i][j];

            newimage[x+1] [y]=image[i][j];
            y+=2;
         }
            x+=2;
            y=0;
      }
   }
// top right side 
   else if(z==3){
      // loop on the top right side of image
      for (int i = 0; i < SIZE/2; i++) {
         for (int j = 128; j< SIZE; j++) {
            // her we repeat every pixel 4 times
            newimage[x][y]=image[i][j];

            newimage[x] [y+1]=image[i][j];

            newimage[x+1] [y+1]=image[i][j];

            newimage[x+1] [y]=image[i][j];
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
            // her we repeat every pixel 4 times
            newimage[x][y]=image[i][j];

            newimage[x] [y+1]=image[i][j];

            newimage[x+1] [y+1]=image[i][j];

            newimage[x+1] [y]=image[i][j];
            y+=2;
         }
            x+=2;
            y=0;
      }
   }
   // save newimage in image
   for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j< SIZE; j++) {
         image[i][j]=newimage[i][j];
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
            newimage[k][l] = image[i][j];
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
            newimage[k][l] = image[i][j];
            l++;
         }
         l=0;
         k++;
      }

   }
   else if (shrinkage == 3)
   {
      //loop through all the pixels , while skipping 3 pixels each time
      for(int i=0; i<SIZE; i+=4) {
         for (int j = 0; j < SIZE; j+=4) {
            newimage[k][l] = image[i][j];
            l++;
         }
         l=0;
         k++;
      }
   }
}
// ______________________________________________________________________________________________________________________________________

void mirror_image(){
   int x;
   cout <<"1-if you want 1/2 right\n2-if you want 1/2 left\n3-if you want 1/2 lower\n4-if you want 1/2 upper\n\n ";
   cout<<"Enter your choice : ";
   cin >> x;
   if (x == 1)
   {
      for (int i = 0; i < SIZE; i++){
         for (int j = 0; j < SIZE; j++){
         image[i][j]= image[i][SIZE-j];
         }
      }
   }
   if (x == 2){
      for (int i = 0; i < SIZE; i++) {
         for (int j = SIZE/2; j < SIZE; j++) {
         image[i][j] = image[i][SIZE-j];
         }
      }
   }
   if (x == 3){
      for (int i = 0; i < SIZE; i++){
         for (int j = 0; j < SIZE; j++){
            image[i][j]= image[SIZE-1-i][j];
         }
      }
   }
   if (x == 4){
      for (int i = 0; i < SIZE; i++){
         for (int j = 0; j < SIZE; j++){
            image[SIZE-1-i][j]= image[i][j];
         }
      }
   }
}
// _______________________________________________________________________________________________________________________________________

void Shuffle_Image(){
   int a,b,c,d,x=0,y=0;
   cout<<"please enter the arrange of photos :";
   cin>>a>>b>>c>>d;
      // top left side 
      for (int i = 0; i < SIZE/2; i++) {
         for (int j = 0; j< SIZE/2; j++) {
            // assign part 1 to top left side 
            ShuffleImage[0][x][y]=image[i][j];
            y+=1;
         }
         y=0;
         x+=1;
      }
      x=0;
      // top right side 
      for (int i = 0; i < SIZE/2; i++) {
         for (int j = 128; j< SIZE; j++) {
            // assign part 2 to top right side
            ShuffleImage[1][x][y]=image[i][j];
           y+=1;
         }
         y=0;
         x+=1;
      }
      x=0;
         // down left side
      for (int i = 128; i < SIZE; i++) {
         for (int j = 0; j< SIZE/2; j++) {
            // assign part 4 to down left side
            ShuffleImage[2][x][y]=image[i][j];
            y+=1;
         }
         y=0;
         x+=1;
      } 
      x=0;
      // down right side

      for (int i = 128; i < SIZE; i++) {
         for (int j = 128; j< SIZE; j++) {
            // assign part 4 to down right side
            ShuffleImage[3][x][y]=image[i][j];
            y+=1;
         }
         y=0;
         x+=1;
      }
      x=0;

      // save ShuffleImage in image ( top left side ) 
      for (int i = 0; i < SIZE/2; i++) {
         for (int j = 0; j< SIZE/2; j++) {
            image[i][j]=ShuffleImage[a-1][x][y];
           y+=1;
         }
         y=0;
         x+=1;
      }
      x=0;
      // save ShuffleImage in image ( top right side ) 
      for (int i = 0; i < SIZE/2; i++) {
         for (int j = 128; j< SIZE; j++) {
            image[i][j]=ShuffleImage[b-1][x][y];
           y+=1;
         }
         y=0;
         x+=1;
      }
      x=0;
      // save ShuffleImage in image (down left side)
      for (int i = 128; i < SIZE; i++) {
         for (int j = 0; j< SIZE/2; j++) {
            image[i][j]=ShuffleImage[c-1][x][y];
           y+=1;
         }
         y=0;
         x+=1;
      }
      x=0;
      // save ShuffleImage in image (down right side)
      for (int i = 128; i < SIZE; i++) {
         for (int j = 128; j< SIZE; j++) {
            image[i][j]=ShuffleImage[d-1][x][y];
           y+=1;
         }
         y=0;
         x+=1;
      }
      x=0;
}
// ______________________________________________________________________________________________________________________________________

/*function that blurs the loaded image and saves it*/
void blur()
{
   for(int i=0; i<SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
         newimage[i][j] = (image[i+1][j+1]*0.12 + image[i][j+1]*0.12 + 
         image[i+1][j]*0.12 + image[i-1][j-1]*0.12 + image[i][j-1]*0.12 + 
         image[i-1][j]*0.12 + image[i-1][j+1]*0.12 + image[i+1][j-1]*0.120 + image[i][j]*0.120/9);
      }
   }
}
// ______________________________________________________________________________________________________________________________________

void crop_image(){
    int x,y,l,w;
    cout << "enter x y l w: ";
    cin >> x >> y >> l >> w;
    for(int i=0; i < 256; i++){
        for(int j=0; j < 256; j++) {
            if(!(j >= x && j <= (x+w) && i >= y && i <= (y+l-1)))
                image[i][j] = 255;
   }
}

}









