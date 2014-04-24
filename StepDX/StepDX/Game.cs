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

        private HorizontalPlat currentPlat = new HorizontalPlat();
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
        private Texture finishLineTexture;
        private ProjectileGenerator projectileGen;
        private Microsoft.DirectX.Direct3D.Font font;

        private int scoreLostPerSecond = 10;
        private int score = 1000;

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

            font = new Microsoft.DirectX.Direct3D.Font(device,  // Device we are drawing on
                    40,         // Font height in pixels
                    0,          // Font width in pixels or zero to match height
                    FontWeight.Bold,    // Font weight (Normal, Bold, etc.)
                    0,          // mip levels (0 for default)
                    false,      // italics?
                    CharacterSet.Default,   // Character set to use
                    Precision.Default,      // The font precision, try some of them...
                    FontQuality.Default,    // Quality?
                    PitchAndFamily.FamilyDoNotCare,     // Pitch and family, we don't care
                    "Arial");               // And the name of the font

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
            finishLineTexture = TextureLoader.FromFile(device, "../../finishlineplatform.bmp");
            projectileGen = new ProjectileGenerator(device);
            
            Polygon startingPlat = new Polygon();
            startingPlat.AddVertex(new Vector2(0, .1f));
            startingPlat.AddVertex(new Vector2(.5f, .1f));
            startingPlat.AddVertex(new Vector2(.5f, 0));
            startingPlat.AddVertex(new Vector2(0, 0));
            startingPlat.Color = Color.CornflowerBlue;
            world.Add(startingPlat);

            Platform platform = new Platform();
            platform.AddVertex(new Vector2(3.2f, 2));
            platform.AddVertex(new Vector2(3.9f, 2));
            platform.AddVertex(new Vector2(3.9f, 1.8f));
            platform.AddVertex(new Vector2(3.2f, 1.8f));
            platform.Color = Color.GreenYellow;
            world.Add(platform);

            Platform platform4 = new Platform();
            platform4.AddVertex(new Vector2(21, 2));
            platform4.AddVertex(new Vector2(21.5f, 2));
            platform4.AddVertex(new Vector2(21.5f, 1.8f));
            platform4.AddVertex(new Vector2(21, 1.8f));
            platform4.Color = Color.IndianRed;
            world.Add(platform4);

            Platform platform5 = new Platform();
            platform5.AddVertex(new Vector2(23, 2));
            platform5.AddVertex(new Vector2(23.5f, 2));
            platform5.AddVertex(new Vector2(23.5f, 1.8f));
            platform5.AddVertex(new Vector2(23, 1.8f));
            platform5.Color = Color.MediumSeaGreen;
            platform5.setDtOffset(0.01f);
            world.Add(platform5);

            HorizontalPlat platform2 = new HorizontalPlat();
            platform2.AddVertex(new Vector2(11, 2));
            platform2.AddVertex(new Vector2(11.7f, 2));
            platform2.AddVertex(new Vector2(11.7f, 1.8f));
            platform2.AddVertex(new Vector2(11.2f, 1.8f));
            platform2.Speed = 2.5f;
            platform2.Color = Color.Red;
            platform2.Width = 4;
            world.Add(platform2);

            //addTexturedPolygon(left, right, bottom, top, outer, texture)
            addTexturedPolygon(1.2f, 1.9f, 1.4f, 1.6f, 1.3f, stoneTexture); //1st plat
            addTexturedPolygon(6, 7, 1.7f, 1.9f, 1.5f, texture1);   //3rd after moving

            addTexturedPolygon(9, 10, 1.2f, 1.4f, 1.0f, texture4);
            addTexturedPolygon(15, 16, 2.5f, 2.7f, 2.0f, texture5);
            addTexturedPolygon(18, 20, 2.2f, 2.4f, 1.5f, texture2);
            addTexturedPolygon(24.5f, 25, 2.2f, 2.4f, 1.5f, texture3);
            addTexturedPolygon(27, 29, 2.2f, 2.4f, 1.5f, texture6);

            FinishPlat pt = new FinishPlat();
            pt.Tex = finishLineTexture;
            pt.AddVertex(new Vector2(30, 1.5f)); //A
            pt.AddTex(new Vector2(0, 0));
            pt.AddVertex(new Vector2(32, 1.5f)); //B
            pt.AddTex(new Vector2(1, 0));
            pt.AddVertex(new Vector2(32, 0.5f)); //C
            pt.AddTex(new Vector2(1, 1));
            pt.AddVertex(new Vector2(30, 0.5f));
            pt.AddTex(new Vector2(0, 1));
            pt.Color = Color.Transparent;
            world.Add(pt);

            Texture spritetexture = TextureLoader.FromFile(device, "../../mario8.png");
            player.Tex = spritetexture;
            player.AddVertex(new Vector2(-0.4f, 0));
            player.AddTex(new Vector2(0, 1));
            player.AddVertex(new Vector2(-0.4f, 0.5f));
            player.AddTex(new Vector2(0, 0));
            player.AddVertex(new Vector2(0.4f, 0.5f));
            player.AddTex(new Vector2(0.125f, 0));
            player.AddVertex(new Vector2(0.4f, 0));
            player.AddTex(new Vector2(0.125f, 1));
            player.Color = Color.Transparent;
            player.Transparent = true;
            player.P = new Vector2(0.5f, 1);
            player.A = new Vector2(0, -9.8f);
            currentPlat = null;
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

            score = 1000 - (int)time / 100;
            if (score < 0)
            {
                GameOver();
            }
            currentPlat = null;
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
                player.isStanding = false;
                foreach (Polygon p in world)
                {

                    if (collision.Test(player, p))
                    {
                        float depth = collision.P1inP2 ?
                                  collision.Depth : -collision.Depth;
                        player.P = player.P + collision.N * depth;
                        Vector2 v = player.V;
                        if (p is Projectile)
                        {
                            if (collision.N.Y != -1 && collision.N.X == 0)
                            {
                                v.Y = -1 * player.V.Y;
                                v.Y = (v.Y < 5) ? v.Y : 5;
                                player.V = v;
                                ((Projectile)p).DropRate = -5;
                                continue;
                            }
                            else
                            {
                                PlayerDied();
                                continue;
                            }
                        }
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
                            if (p is Platform)
                            {
                                Platform x = (Platform)p;
                                Vector2 v2 = player.V;
                                v.Y = x.GetSpeed;
                                player.V = v;
                                player.isStanding = true;
                            }
                            if (p is HorizontalPlat)
                            {
                                HorizontalPlat x = (HorizontalPlat)p;
                                Vector2 v2 = player.V;
                                currentPlat = x;
                                v.X = x.GetSpeed;
                                player.isStanding = true;

                            }
                            if (p is FinishPlat)
                            {
                                GameWon();
                            }
                        }


                            player.V = v;
                            player.Advance(0);
                        
                    }

                }
                world = projectileGen.Advance(delta, world);
                delta -= step;
            }
            //Check to see if we need a reset
            if (player.P.Y < -.5f)
            {
                PlayerDied();
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

            font.DrawText(null,     // Because I say so
            "Score: " + score,            // Text to draw
            new Point(1, 3),  // Location on the display (pixels with 0,0 as upper left)
            Color.LightCyan);   // Font color


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
                if (currentPlat != null)
                    v.X = 1.5f + currentPlat.GetSpeed; 
                player.V = v;
                player.isMoving = true;
            }
            else if (e.KeyCode == Keys.Left)
            {
                Vector2 v = player.V;
                v.X = -1.5f;
                if (currentPlat != null)
                    v.X = -1.5f + currentPlat.GetSpeed; 
                player.V = v;
                player.isMoving = true;
            }
            else if (e.KeyCode == Keys.Space)
            {
                if (player.isStanding)
                {
                    sounds.Jump();
                    player.isStanding = false;
                    Vector2 v = player.V;
                    v.Y = 6.5f;
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
                player.isMoving = false;
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
        private void ResetGame()
        {
            player.P = new Vector2(0.5f, 1);
            player.V = new Vector2(0, 0);
            player.A = new Vector2(0, -9.8f);
            player.isStanding = true;
            player.isMoving = false;
            stopwatch.Start();
        }

        private void PlayerDied()
        {
            sounds.Die();
            ResetGame();
        }

        private void GameOver()
        {
            sounds.GameOver();
            System.Windows.Forms.MessageBox.Show("You lose!");
            stopwatch.Reset();
            ResetGame();
        }

        private void GameWon()
        {
            sounds.GameWon();
            System.Windows.Forms.MessageBox.Show("You Win!\n Score: " + score);
            stopwatch.Reset();
            ResetGame();
        }


    }
}