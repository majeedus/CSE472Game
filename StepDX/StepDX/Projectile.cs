using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
namespace StepDX
{
    public class Projectile : PolygonTextured
    {

                  /// <summary>
        /// Vertices after we move them
        /// </summary>
        protected List<Vector2> verticesM = new List<Vector2>();

        /// <summary>
        /// Vertices after they have been moved
        /// </summary>
        public override List<Vector2> Vertices { get { return verticesM; } }

        /// <summary>
        /// Current time for the object
        /// </summary>
        private float time = 0;

        /// <summary>
        /// For saving the state
        /// </summary>
        private float saveTime = 0;

        /// <summary>
        /// Speed in meters per second
        /// </summary>
        private float speed = 1;

        /// <summary>
        /// How wide we go
        /// </summary>
        float maxWidth = 32;

        public float Speed {get {return speed;} set { speed = value;}}

        /// <summary>
        /// Save the current platform position state
        /// </summary>
        public void SaveState()
        {
            saveTime = time;
        }

        /// <summary>
        /// Restore the current platform position state
        /// </summary>
        public void RestoreState()
        {
            time = saveTime;
        }
        public float GetLocation()
        {
            if (Vertices.Count > 0)
            {

                float minX = Vertices[0].X;
                foreach (Vector2 v in Vertices)
                {

                    if (v.X < minX || minX == -1)
                    {
                        minX = v.X;
                    }
                }
                return minX;
            }
            return 0;
        }
        /// <summary>
        /// Advance the platform animation in time
        /// </summary>
        /// <param name="dt">The delta time in seconds</param>
        public override void Advance(float dt)
        {
            time += dt;

            // I'm going to base my height entirely on the current time.
            // From 0 to speed, we are rising, speed to 2*speed we are 
            // falling.  So we need to know what step we are in.
            float w;

            int step = (int)(time / speed);

                // Even, rising
            w = -maxWidth * (time - step * speed) / speed;


            // Move it
            verticesM.Clear();
            foreach (Vector2 v in verticesB)
            {
                verticesM.Add(v + new Vector2(w, 0));
            }

        

        }
    }
}
