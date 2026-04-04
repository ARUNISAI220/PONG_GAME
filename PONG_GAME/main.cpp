#include <raylib.h>

struct Ball 
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Drwaw() 
	{
		DrawCircle((int)x, (int)y, radius, RED);
	}
};
struct Paddle
{
	float x, y;
	float width, height;
	float speed;
	
	Rectangle GetRect()
	{
		return Rectangle { x - width / 2, y - height / 2, 10,100 };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};

int main()
{
	InitWindow(800, 600, "Pong Game");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 10;
	ball.speedX = 300;
	ball.speedY = 500;

	Paddle leftpaddle;
	leftpaddle.x = 50;
	leftpaddle.y = GetScreenHeight() / 2;
	leftpaddle.width = 10;
	leftpaddle.height = 100;
	leftpaddle.speed = 500;

	Paddle rightpaddle;
	rightpaddle.x = GetScreenWidth() - 50;
	rightpaddle.y = GetScreenHeight() / 2;
	rightpaddle.width = 10;
	rightpaddle.height = 100;
	rightpaddle.speed = 500;
	const char* winnerText = nullptr;

	while (!WindowShouldClose())
	{
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if(ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}
	
		if (IsKeyDown(KEY_W))
		{
			leftpaddle.y -= leftpaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			leftpaddle.y += leftpaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP))
		{
			rightpaddle.y -= rightpaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			rightpaddle.y += rightpaddle.speed * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftpaddle.GetRect()))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftpaddle.y) / (leftpaddle.height / 2) * ball.speedX;
			}
			
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightpaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightpaddle.y) / (rightpaddle.height / 2) * ball.speedX;
			}
		}

		if (ball.x < 0)
		{
			winnerText = "Right Player Wins!";
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Player Wins!";
		}
		if (winnerText && IsKeyPressed(KEY_ENTER))
		{
			ball.x = GetScreenWidth() / 2.0f;
			ball.y = GetScreenHeight() / 2.0f;
			ball.speedX = 300;
			ball.speedY = 500;
			winnerText = nullptr;
		}
	
		BeginDrawing();
		ClearBackground(BLACK);
		
		ball.Drwaw();
		leftpaddle.Draw();
		rightpaddle.Draw();

		if (winnerText)
		{
			int textWith = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWith / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		}

		DrawFPS(10, 10);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}