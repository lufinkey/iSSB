package com.brokenphysics.issb;

import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity {
	/**
	 * A native method that is implemented by the 'native-lib' native library,
	 * which is packaged with this application.
	 */
	public native String stringFromJNI();

	protected String[] getLibraries() {
		return new String[] {
				"hidapi",
				"SDL2",
				"SDL2_image",
				"SDL2_mixer",
				//"SDL2_net",
				"SDL2_ttf",
				"iSSBLib"
		};
	}
}