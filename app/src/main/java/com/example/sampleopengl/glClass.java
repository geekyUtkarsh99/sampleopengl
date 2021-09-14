package com.example.sampleopengl;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class glClass extends GLSurfaceView {


    private final renderGl renderer ;

    public glClass(Context context) {
        super(context);

        setEGLContextClientVersion(2);
        renderer = new renderGl(context);
        setRenderer(renderer);

    }


}
