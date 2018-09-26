// Vídeo aula
// https://www.youtube.com/watch?v=OjNClUIDgt8
// https://www.youtube.com/watch?v=pUCf0hfU6no

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

string intToString(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}

int main(int argc, char* argv[]){
	Mat frame;
	VideoCapture cap(0); // open the video camera no. 0
	
	if (!cap.isOpened()){  // if not success, exit program
		cout << "ERROR INITIALIZING VIDEO CAPTURE" << endl;
		return -1;
	}
	char* windowName = "Webcam Feed";
	namedWindow(windowName,CV_WINDOW_AUTOSIZE); //create a window to display our webcam feed
    VideoWriter writer("video.avi", CV_FOURCC('M','J','P','G'), 15, Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT)),true);
	if(!writer.isOpened()){
		cout<<"ERROR OPENING FILE FOR WRITE\n"; getchar();
		return -1;
	}

	while(1) {
		bool bSuccess = cap.read(frame); // read a new frame from camera feed
		if (!bSuccess){ //test if frame successfully read
			cout << "ERROR READING FRAME FROM CAMERA FEED" << endl;
			break;
		}

		writer.write(frame);
		imshow(windowName, frame); //show the frame in "MyVideo" window

        //listen for 10ms for a key to be pressed
        switch (waitKey(10)){
        case 27:
            //'esc' has been pressed (ASCII value for 'esc' is 27)
            //exit program.
            return 0;
        }
    }
	return 0;
}