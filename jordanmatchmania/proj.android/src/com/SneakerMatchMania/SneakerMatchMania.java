/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.SneakerMatchMania;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.json.JSONObject;

import com.playhaven.src.common.PHAPIRequest;
import com.playhaven.src.publishersdk.content.PHContent;
import com.playhaven.src.publishersdk.content.PHPublisherContentRequest;
import com.playhaven.src.publishersdk.content.PHPublisherContentRequest.ContentDelegate;
import com.playhaven.src.publishersdk.content.PHPublisherContentRequest.PHDismissType;
import com.playhaven.src.publishersdk.metadata.PHNotificationView;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import com.diwublog.AnalyticX.AnalyticXBridge;
import com.revmob.cocos2dx.RevMobWrapper;
import com.wenbin.ChartboostX.*;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;

public class SneakerMatchMania extends Cocos2dxActivity implements ContentDelegate {
	
	private static final String TAG = "SneakerMatchMania";
	public static SneakerMatchMania me;
	static Context myAndroidContext;
	
	//////////////////////////////////////////////////////////////
	// 					Lifecicle								//
	//////////////////////////////////////////////////////////////

	private static final String heavenToken = "bac9bcb3bd154094898be5649609adc9";
	private static final String heavenSecret = "ac62974b9bec4869a8378b0f96ef1987"; 
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);		
		myAndroidContext = getApplicationContext();
		ChartboostXBridge.initChartboostXBridge(this);
		RevMobWrapper.setActivity(this);
		AnalyticXBridge.sessionContext = this.getApplicationContext();
		//IAPManager.InitializeIAPManager();
		
		// for playheaven
		com.playhaven.src.common.PHConfig.token = heavenToken;
		com.playhaven.src.common.PHConfig.secret = heavenSecret;
		me = this;
	}
	
//////////////////////////////////////////////////////////////
// 					Interface  								//
//////////////////////////////////////////////////////////////
	static public boolean isInternetConnection()
	{
		Log.v("InternetConnection", "isInternetConnection Start");
		/*
		// Toast make fail DEMO ! :S
		Toast toast1 =	Toast.makeText(myAndroidContext,
		"Checking Internet", Toast.LENGTH_SHORT);
		toast1.show();
		 */
		
		ConnectivityManager conMgr =  (ConnectivityManager)myAndroidContext.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo i = conMgr.getActiveNetworkInfo();

		if (i == null)
		{
			Log.v("InternetConnection", "isInternetConnection NULL :S");
			return false;
		}

		if (!i.isConnected())
		{
			Log.v("InternetConnection", "isInternetConnection is not connected");
			return false;
		}

		if (!i.isAvailable())
		{
			Log.v("InternetConnection", "isInternetConnection is not available");
			return false;
		}
		Log.v("InternetConnection", "isInternetConnection DONE!");

		return true;   	
	}
	private static void sendEMail()
	{
		Log.d("activity", "Send a email on Java");
		Intent i = new Intent(Intent.ACTION_SEND);
		//i.setType("text/plain"); //use this line for testing in the emulator
		i.setType("message/rfc822") ; // use from live device
		i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);	
		i.putExtra(Intent.EXTRA_EMAIL, new String[]{"test@gmail.com"});
		i.putExtra(Intent.EXTRA_SUBJECT,"Check out this cool game...");
		i.putExtra(Intent.EXTRA_TEXT,"Hey, I 've been playing this free sneaker game that I think you'll love. careful...it's addictive! http://goo.gl/O8an6V");
		myAndroidContext.startActivity(i);
	}
	
	private static void sendEmailSupport()
	{
		Log.d("activity", "Send a email on Java with Support");
		
		Context curContext = getContext();
		
		// get version number
		String  versionName = "0.0";
		try {
			PackageInfo packageInfo = curContext.getPackageManager().getPackageInfo(curContext.getPackageName(), 0);
			versionName = packageInfo.versionName;
		}
		catch (NameNotFoundException e)
		{
			versionName = "0.0";
		}
						
		Intent i = new Intent(Intent.ACTION_SEND);
		//i.setType("text/plain"); //use this line for testing in the emulator
		i.setType("message/rfc822") ; // use from live device
		i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);	
		i.putExtra(Intent.EXTRA_EMAIL, new String[]{"support@narleyapps.com"});
		i.putExtra(Intent.EXTRA_SUBJECT,"Sneaker Match Mania v" + versionName);
		i.putExtra(Intent.EXTRA_TEXT,"Message Here. <br/><br/><br/>Locale: " + java.util.Locale.getDefault().getDisplayName() 
				+ "<br/>Device Model:" + android.os.Build.MODEL
				+ "<br/>App Version:" + versionName);
		myAndroidContext.startActivity(i);		
	}
	
	private static void showMoreApp()
	{
		Log.d("activity", "Show more apps");
		
		if (me == null)
			return;
		
		// create heaven request and send
		PHPublisherContentRequest request = new PHPublisherContentRequest(me, me, "more_games");
		request.setOverlayImmediately(true);
		request.setOnContentListener(me);
		request.preload();
		request.send();
	}
//////////////////////////////////////////////////////////////
// 					OpenGL   								//
//////////////////////////////////////////////////////////////
	public Cocos2dxGLSurfaceView onCreateView() 
	{
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		// CCSocialNetwork should create stencil buffer
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

		return glSurfaceView;	
	}
	 
	 
    static {
         System.loadLibrary("game");
    }


    // ContentDelegate functions
	@Override
	public void requestFailed(PHAPIRequest arg0, Exception arg1) {
		// TODO Auto-generated method stub
		Log.d("Playheaven", "requestFailed");
	}

	@Override
	public void requestSucceeded(PHAPIRequest arg0, JSONObject arg1) {
		// TODO Auto-generated method stub
		Log.d("Playheaven", "requestSucceeded");
		
	}

	@Override
	public void didDismissContent(PHPublisherContentRequest arg0,
			PHDismissType arg1) {
		// TODO Auto-generated method stub
		Log.d("Playheaven", "didDismissContent");
		
	}

	@Override
	public void didDisplayContent(PHPublisherContentRequest arg0, PHContent arg1) {
		// TODO Auto-generated method stub
		Log.d("Playheaven", "didDisplayContent");
		
	}

	@Override
	public void willDisplayContent(PHPublisherContentRequest arg0,
			PHContent arg1) {
//		Intent i = new Intent(myAndroidContext, MoreAppActivity.class);
//		i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);	
//		myAndroidContext.startActivity(i);
	}

	@Override
	public void willGetContent(PHPublisherContentRequest arg0) {
		// TODO Auto-generated method stub
		Log.d("playheaven", "willGetContent");
	}
}
