package com.example.sampleopengl;

import android.content.Context;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.view.animation.CycleInterpolator;

import androidx.core.content.ContextCompat;

import java.util.function.IntUnaryOperator;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class renderGl implements GLSurfaceView.Renderer {

    private Context context = null;

    public renderGl(Context context){

        this.context = context;

    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        try{
            libHolder.getImage(BitmapFactory.decodeResource(context.getResources(),R.drawable.img3).toString().toCharArray());
            libHolder.changeSurface(width,height);
        }catch (Exception e){
            e.printStackTrace();
        }

    }

    @Override
    public void onDrawFrame(GL10 gl) {
        try {
            libHolder.createSurface();
        }catch (Exception e){
            e.printStackTrace();
        }

    }


}
