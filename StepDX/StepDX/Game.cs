using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace StepDX
{
    public partial class Game : Form
    {
        /// <summary>
        /// The DirectX device we will draw on
        /// </summary>
        private Device device = null;

        /// <summary>
        /// Height of our playing area (meters)
        /// </summary>
        private float playingH = 4;

        /// <summary>
        /// Width of our playing area (meters)
        /// </summary>
        private float playingW = 32;

        /// <summary>
        /// Vertex buffer for our drawing
        /// </summary>
        private VertexBuffer vertices = null;

        /// <summary>
        /// The background image class
        /// </summary>
        private Background background = null;

        /// <summary>
        /// All of the polygons that make up our world
        /// </summary>
        List<Polygon> world = new List<Polygon>();

        /// <summary>
        /// What the last time reading was
        /// </summary>
        private long lastTime;

        /// <summary>
        /// A stopwatch to use to keep track of time
        /// </summary>
        private System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();

        /// <summary>
        /// Our player sprite
        /// </summary>
        GameSprite player = new GameSprite();

        /// <summary>
        /// The collision testing subsystem
        /// </summary>
        Collision collision = new Collision();

        private Texture texture1;
        private Texture texture2;
        private Texture texture3;
        private Texture texture4;
        private Texture texture5;
        private Texture texture6;
        private Texture stoneTexture;

        /// <summary>
        /// Jump sounds class
        /// </summary>
        private GameSounds sounds;

        public Game()
        {
            InitializeComponent();

            if (!InitializeDirect3D())
                return;

            sounds = new GameSounds(this);

            vertices = new VertexBuffer(typeof(CustomVertex.PositionColored), // Type of vertex
                                        4,      // How many
                                        device, // What device
                                        0,      // No special usage
                                        CustomVertex.PositionColored.Format,
                                        Pool.Managed);

            background = new Background(device, playingW, playingH);

            // Determine the last time
            stopwatch.Start();
            lastTime = stopwatch.ElapsedMilliseconds;

            texture1 = TextureLoader.FromFile(device, "../../texture1.bmp");
            texture2 = TextureLoader.FromFile(device, "../../texture2.bmp");
            texture3 = TextureLoader.FromFile(device, "../../texture3.bmp");
            texture4 = TextureLoader.FromFile(device, "../../texture4.bmp");
            texture5 = TextureLoader.FromFile(device, "../../texture5.bmp");
            texture6 = TextureLoader.FromFile(device, "../../texture6.bmp");
            stoneTexture = TextureLoader.FromFile(device, "../../stone08.bmp");
            
            Polygon startingPlat = new Polygon();
            startingPlat.AddVertex(new Vector2(0, .1f));
            startingPlat.AddVertex(new Vector2(.5f, .1f));
            startingPlat.AddVertex(new Vector2(.5f, 0));
            startingPlat.AddVertex(new Vector2(0, 0));
            startingPlat.Color = Color.CornflowerBlue;
            world.Add(startingPlat);
            
            
            /* Remove this code later
            AddObstacle(2, 3, 1.7f, 1.9f, Color.Crimson);
            AddObstacle(4, 4.2f, 1, 2.1f, Color.Coral);
            AddObstacle(5, 6, 2.2f, 2.4f, Color.BurlyWood);
            AddObstacle(5.5f, 6.5f, 3.2f, 3.4f, Color.PeachPuff);
            AddObstacle(6.5f, 7.5f, 2.5f, 2.7f, Color.Chocolate);
            */

            Platform platform = new Platform();
            platform.AddVertex(new Vector2(3.2f, 2));
            platform.AddVertex(new Vector2(3.9f, 2));
            platform.AddVertex(new Vector2(3.9f, 1.8f));
            platform.AddVertex(new Vector2(3.2f, 1.8f));
            platform.Color = Color.CornflowerBlue;
            world.Add(platform);

            HorizontalPlat platform2 = new HorizontalPlat();
            platform2.AddVertex(new Vector2(11.2f, 2));
            platform2.AddVertex(new Vector2(11.7f, 2));
            platform2.AddVertex(new Vector2(11.7f, 1.8f));
            platform2.AddVertex(new Vector2(11.2f, 1.8f));
            platform2.Speed = 1;
            platform.Color = Color.Red;
            world.Add(platform2);

            //addTexturedPolygon(left, right, bottom, top, outer, path)
            addTexturedPolygon(1.2f, 1.9f, 1.4f, 1.6f, 1.3f, stoneTexture); //1st plat
            addTexturedPolygon(6, 7, 1.7f, 1.9f, 1.5f, texture1);   //3rd after moving

            addTexturedPolygon(9, 10, 1.2f, 1.4f, 1.0f, texture4);
            addTexturedPolygon(15, 16, 2.5f, 2.7f, 2.0f, texture5);
            addTexturedPolygon(18, 20, 2.2f, 2.4f, 1.5f, texture2);
            /* Remove this code later...
            Texture texture = TextureLoader.FromFile(device, "../../stone08.bmp");
            PolygonTextured pt = new PolygonTextured();
            pt.Tex = texture;
            pt.AddVertex(new Vector2(1.2f, 3.5f));
            pt.AddTex(new Vector2(0, 1));
            pt.AddVertex(new Vector2(1.9f, 3.5f));
            pt.AddTex(new Vector2(0, 0));
            pt.AddVertex(new Vector2(1.9f, 3.3f));
            pt.AddTex(new Vector2(1, 0));
            pt.AddVertex(new Vector2(1.2f, 3.3f));
            pt.AddTex(new Vector2(1, 1));
            pt.Color = Color.Transparent;
            world.Add(pt);
            */

            Texture spritetexture = TextureLoader.FromFile(device, "../../guy8.bmp");
            player.Tex = spritetexture;
            player.AddVertex(new Vector2(-0.2f, 0));
            player.AddTex(new Vector2(0, 1));
            player.AddVertex(new Vector2(-0.2f, 1));
            player.AddTex(new Vector2(0, 0));
            player.AddVertex(new Vector2(0.2f, 1));
            player.AddTex(new Vector2(0.125f, 0));
            player.AddVertex(new Vector2(0.2f, 0));
            player.AddTex(new Vector2(0.125f, 1));
            player.Color = Color.Transparent;
            player.Transparent = true;
            player.P = new Vector2(0.5f, 1);
            player.A = new Vector2(0, -9.8f);

        }

        public void addTexturedPolygon(float left, float right, float bottom, float top, float outer, Texture texture)
        {
            PolygonTextured pt = new PolygonTextured();
            pt.Tex = texture;
            pt.AddVertex(new Vector2(left, top)); //A
            pt.AddTex(new Vector2(0, 1));
            pt.AddVertex(new Vector2(right, top)); //B
            pt.AddTex(new Vector2(0.5f, 0));
            pt.AddVertex(new Vector2(right, bottom)); //C
            pt.AddTex(new Vector2(1, 0.5f));
            pt.AddVertex(new Vector2((left+right)/2.0f, outer)); //D
            pt.AddTex(new Vector2(1, 1));
            pt.AddVertex(new Vector2(left, bottom));
            pt.AddTex(new Vector2(0, 0.5f));
            pt.Color = Color.Transparent;
            world.Add(pt);
        }

        /// <summary>
        /// Advance the game in time
        /// </summary>
        public void Advance()
        {
            // How much time change has there been?
            long time = stopwatch.ElapsedMilliseconds;
            float delta = (time - lastTime) * 0.001f;       // Delta time in milliseconds
            lastTime = time;

            while (delta > 0)
            {

                float step = delta;
                if (step > 0.05f)
                    step = 0.05f;
                


                float maxspeed = Math.Max(Math.Abs(player.V.X), Math.Abs(player.V.Y));
                if (maxspeed > 0)
                {
                    step = (float)Math.Min(step, 0.05 / maxspeed);
                }

                player.Advance(step);

                foreach (Polygon p in world)
                    p.Advance(step);

                foreach (Polygon p in world)
                {
                    if (collision.Test(player, p))
                    {
                        float depth = collision.P1inP2 ?
                                  collision.Depth : -collision.Depth;
                        player.P = player.P + collision.N * depth;
                        Vector2 v = player.V;
                        
                        if (collision.N.X != 0)
                        {
                            v.X = 0;
                        }
                        if (collision.N.Y != 0)
                        {
                            v.Y = 0;
                            if (collision.N.Y != -1)
                            {
                                //Check that player didn't just hit its head on ceiling
                                player.isStanding = true;
                            }
                        }

                        player.V = v;
                        player.Advance(0);
                    }
                    else
                    {
                        //Player is not colliding with anything.
                        if (player.V.Y != 0)
                        {
                             player.isStanding = false;
                        }
                    }
                }

                delta -= step;
            }
            //Check to see if we need a reset
            if (player.P.Y < -.5f)
            {
                Reset();
            }
        }


        public void Render()
        {
            if (device == null)
                return;

            device.Clear(ClearFlags.Target, System.Drawing.Color.Blue, 1.0f, 0);

            int wid = Width;                            // Width of our display window
            int hit = Height;                           // Height of our display window.
            float aspect = (float)wid / (float)hit;     // What is the aspect ratio?

            device.RenderState.ZBufferEnable = false;   // We'll not use this feature
            device.RenderState.Lighting = false;        // Or this one...
            device.RenderState.CullMode = Cull.None;    // Or this one...

            float widP = playingH * aspect;         // Total width of window

            float winCenter = player.P.X;
            if (winCenter - widP / 2 < 0)
                winCenter = widP / 2;
            else if (winCenter + widP / 2 > playingW)
                winCenter = playingW - widP / 2;

            device.Transform.Projection = Matrix.OrthoOffCenterLH(winCenter - widP / 2,
                                                                  winCenter + widP / 2,
                                                                  0, playingH, 0, 1);

            //Begin the scene
            device.BeginScene();

            // Render the background
            background.Render();

            foreach (Polygon p in world)
            {
                p.Render(device);
            }

            player.Render(device);

            //End the scene
            device.EndScene();
            device.Present();
        }

        /// <summary>
        /// Initialize the Direct3D device for rendering
        /// </summary>
        /// <returns>true if successful</returns>
        private bool InitializeDirect3D()
        {
            try
            {
                // Now let's setup our D3D stuff
                PresentParameters presentParams = new PresentParameters();
                presentParams.Windowed = true;
                presentParams.SwapEffect = SwapEffect.Discard;

                device = new Device(0, DeviceType.Hardware, this, CreateFlags.SoftwareVertexProcessing, presentParams);
            }
            catch (DirectXException)
            {
                return false;
            }

            return true;
        }

        protected override void OnKeyDown(System.Windows.Forms.KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
                this.Close(); // Esc was pressed
            else if (e.KeyCode == Keys.Right)
            {
                Vector2 v = player.V;
                v.X = 1.5f;
                player.V = v;
            }
            else if (e.KeyCode == Keys.Left)
            {
                Vector2 v = player.V;
                v.X = -1.5f;
                player.V = v;
            }
            else if (e.KeyCode == Keys.Space)
            {
                if (player.isStanding)
                {
                    sounds.Jump();
                    player.isStanding = false;
                    Vector2 v = player.V;
                    v.Y = 7;
                    player.V = v;
                    player.A = new Vector2(0, -9.8f);
                }
            }
        }

        protected override void OnKeyUp(System.Windows.Forms.KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Right || e.KeyCode == Keys.Left)
            {
                Vector2 v = player.V;
                v.X = 0;
                player.V = v;
            }
        }

        private void AddObstacle(float left, float right, float bottom, float top, Color color)
        {
            Polygon p = new Polygon();
            p.AddVertex(new Vector2(left, bottom));
            p.AddVertex(new Vector2(left, top));
            p.AddVertex(new Vector2(right, top));
            p.AddVertex(new Vector2(right, bottom));
            p.Color = color;
            world.Add(p);
        }
        private void Reset()
        {
            player.P = new Vector2(0.5f, 1);
            player.V = new Vector2(0, 0);
            player.A = new Vector2(0, -9.8f);
            player.isStanding = true;
        }


    }
}