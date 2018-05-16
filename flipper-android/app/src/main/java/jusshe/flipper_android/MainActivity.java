package jusshe.flipper_android;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import java.util.HashMap;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void toggleMethod(View view) {
//        Toast.makeText(getApplicationContext(),"Hello!", Toast.LENGTH_LONG).show();
        final TextView tView = (TextView) findViewById(R.id.tView);

        //Instantiate RequestQueue
        RequestQueue queue = Volley.newRequestQueue(this);
        String url = "http://192.168.1.12/toggle";
//        String url = "http://google.com/";

        //Build a request
        StringRequest toggleRequest = new StringRequest(Request.Method.POST, url,
            new Response.Listener<String>() {
                @Override
                public void onResponse(String response) {
                    // Display the first 500 characters of the response string.
                   tView.setText(response);
                }
            }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                tView.setText("That didn't work!");
            }
        }){
            @Override
            protected Map<String, String> getParams()
            {
                Map<String, String>  params = new HashMap<String, String>();
                params.put("pass", "toggle");
                return params;
            }
        };

        //Add request to the queue
        queue.add(toggleRequest);
    }
}
