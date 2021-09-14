package com.example.sampleopengl;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    //TAG for debugging--
    private static final String TAG = "MainActivity.java";

    // Used to load the 'native-lib' library on application startup.

    GLSurfaceView surface = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN);
        //this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);


        Bitmap image = Bitmap.createScaledBitmap(BitmapFactory.decodeResource(getResources(),R.drawable.img3),1000,1000,false);
        byte[] imageBuffers = image.toString().getBytes();

        libHolder.send_pixel(image,image.getWidth(),image.getHeight());


        surface = new glClass(this);

        setContentView(surface);
        //setContentView(R.layout.activity_main);

        Log.d(TAG, "onCreate: " );



    }

    subThread tr = new subThread(500){
        @Override
        public void run() {
            super.run();
            while (true){

                libHolder.updateVals();
                //Log.d(TAG, "run: ");
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

            }
      }
    };




}