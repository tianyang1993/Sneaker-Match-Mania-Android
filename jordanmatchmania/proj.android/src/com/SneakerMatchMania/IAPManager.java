package com.SneakerMatchMania;

import java.util.HashMap;
import java.util.Map;

import android.app.Activity;
import android.util.Log;

import org.onepf.oms.OpenIabHelper;
import org.onepf.oms.appstore.AmazonAppstore;
import org.onepf.oms.appstore.googleUtils.IabHelper;
import org.onepf.oms.appstore.googleUtils.IabResult;
import org.onepf.oms.appstore.googleUtils.Inventory;
import org.onepf.oms.appstore.googleUtils.Purchase;

public class IAPManager extends Activity {

	static final String IAP_FULL_VERSION = "com.pointabout.66F93tw.remove_banner_ads";
	static final String IAP_ADD_BACKGROUNDS = "com.pointabout.66F93tw.add_backgrounds";
	static final String[] IAP_BYTES_PACK = {
		"com.pointabout.66F93tw.500bytespack",
		"com.pointabout.66F93tw.1000bytespack",
		"com.pointabout.66F93tw.3000bytespack",
		"com.pointabout.66F93tw.7500bytespack",
		"com.pointabout.66F93tw.20000bytespack",
		"com.pointabout.66F93tw.50000bytespack"
	};
	
	static OpenIabHelper mHelper;
    static boolean setupDone = false;
	static void InitializeIAPManager()
	{
		// purchase token from app store
        String base64EncodedPublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAhzHF0MpjpspqZ4+VxjCSs/JDmbPKCWKMLPSiPTCxECoiRoVeDFdStXchsgUWk1ccFs6Y8BbK/wyh5EttsCr21WbpHxbymaO2b8bKCP5BGwHjBeX84qcgBW1or9Z1dMRntdAKrtC14uOm3ICEy0ACmALxibfhZgYmaf9bQ8+kfsLK6RkzISzIFi/ot7vB7cXSFqrTekSb+3PO/HzyE70r0oM0L6QXX/SMMwxK8r5Mb9PywVT6Q2TIlMTBS1VNdP9/jTE3GLtuqGT4m4yi0x7GDnBStexi82n++wrLdQwCHzc+h5+S1k40fgLULumXnjdYhjVY2txKcszlfL0L7qnEVwIDAQAB";

        // Create the helper, passing it our context and the public key to verify signatures with
        Log.d("IAPManager", "Creating IAB helper.");
        Map<String, String> storeKeys = new HashMap<String, String>();
        storeKeys.put(OpenIabHelper.NAME_GOOGLE, base64EncodedPublicKey);

        mHelper = new OpenIabHelper(SneakerMatchMania.myAndroidContext, storeKeys);

        // enable debug logging (for a production application, you should set this to false).
        //mHelper.enableDebugLogging(true);

        // Start setup. This is asynchronous and the specified listener
        // will be called once setup completes.
        Log.d("IAPManager", "Starting setup.");
        mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
            public void onIabSetupFinished(IabResult result) {
                Log.d("IAPManager", "Setup finished.");

                if (!result.isSuccess()) {
                    // Oh noes, there was a problem.
                    Log.d("IAPManager", "Problem setting up in-app billing: " + result);
                    return;
                }

                // Hooray, IAB is fully set up. Now, let's get an inventory of stuff we own.
                Log.d("IAPManager", "Setup successful. Querying inventory.");
                setupDone = true;
                mHelper.queryInventoryAsync(mGotInventoryListener);
            }
        });		
	}
	
    // (arbitrary) request code for the purchase flow
    static final int RC_REQUEST = 10001;
	static void purchaseToken(int tokenID)
	{
		Log.d("JordanMatchMania", "purchase Token() is called = " + IAP_BYTES_PACK[tokenID]);
        if (!setupDone) {
            Log.d("IAPManager", "Billing Setup is not completed yet");
            return;
        }
        // launch the gas purchase UI flow.
        // We will be notified of completion via mPurchaseFinishedListener
        Log.d("IAPManager", "Launching purchase flow for tokens.");
        
        /* TODO: for security, generate your payload here for verification. See the comments on 
         *        verifyDeveloperPayload() for more info. Since this is a SAMPLE, we just use 
         *        an empty string, but on a production app you should carefully generate this. */
        String payload = ""; 
        mHelper.launchPurchaseFlow(SneakerMatchMania.me, IAP_BYTES_PACK[tokenID], RC_REQUEST,  
                mPurchaseFinishedListener, payload);
		
	}

    // Listener that's called when we finish querying the items and subscriptions we own
    static IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
            Log.d("IAPManager", "Query inventory finished.");
            if (result.isFailure()) {
                Log.d("IAPManager", "Failed to query inventory: " + result);
                return;
            }

            Log.d("IAPManager", "Query inventory was successful.");            
        }
    };
    
    /** Verifies the developer payload of a purchase. */
    static boolean verifyDeveloperPayload(Purchase p) {
        String payload = p.getDeveloperPayload();
        
        /*
         * TODO: verify that the developer payload of the purchase is correct. It will be
         * the same one that you sent when initiating the purchase.
         * 
         * WARNING: Locally generating a random string when starting a purchase and 
         * verifying it here might seem like a good approach, but this will fail in the 
         * case where the user purchases an item on one device and then uses your app on 
         * a different device, because on the other device you will not have access to the
         * random string you originally generated.
         *
         * So a good developer payload has these characteristics:
         * 
         * 1. If two different users purchase an item, the payload is different between them,
         *    so that one user's purchase can't be replayed to another user.
         * 
         * 2. The payload must be such that you can verify it even when the app wasn't the
         *    one who initiated the purchase flow (so that items purchased by the user on 
         *    one device work on other devices owned by the user).
         * 
         * Using your own server to store and verify developer payloads across app
         * installations is recommended.
         */
        
        return true;
    }

    // Callback for when a purchase is finished
    static IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
        public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
            Log.d("IAPManager", "Purchase finished: " + result + ", purchase: " + purchase);
            if (result.isFailure()) {
                Log.d("IAPManager", "Error purchasing: " + result);
                return;
            }

            if (!verifyDeveloperPayload(purchase)) {
                Log.d("IAPManager", "Error purchasing. Authenticity verification failed.");
                return;
            }

            Log.d("IAPManager", "Purchase successful.");

            // here purchase code
        }
    };
    
    // Called when consumption is complete
    static IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = new IabHelper.OnConsumeFinishedListener() {
        public void onConsumeFinished(Purchase purchase, IabResult result) {
            Log.d("IAPManager", "Consumption finished. Purchase: " + purchase + ", result: " + result);

            // We know this is the "gas" sku because it's the only one we consume,
            // so we don't check which sku was consumed. If you have more than one
            // sku, you probably should check...
            if (result.isSuccess()) {
                
            	// successfully consumed, so we apply the effects of the item in our
                // game world's logic, which in our case means filling the gas tank a bit
                Log.d("IAPManager", "Consumption successful. Provisioning.");
               
                // HERE: save data
            }
            else {
                Log.d("IAPManager", "Error while consuming: " + result);
            }
            
            Log.d("IAPManager", "End consumption flow.");
        }
    };

    
    
}
