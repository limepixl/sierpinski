#include <SFML/Graphics.hpp>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

void iterate(std::vector<sf::VertexArray>& triangles, int iterations)
{
	std::vector<sf::VertexArray> newlyCreated;

	for(auto& t : triangles)
	{
		sf::Vector2f& first = t[0].position;
		sf::Vector2f& second = t[1].position;
		sf::Vector2f& third = t[2].position;

		// Calculating positions
		sf::Vector2f new1((first.x + second.x) / 2.0f, (first.y + second.y) / 2.0f);
		sf::Vector2f new2((first.x + third.x) / 2.0f, (first.y + third.y) / 2.0f);
		sf::Vector2f new3((second.x + third.x) / 2.0f, (second.y + third.y) / 2.0f);

		// First triangle
		sf::VertexArray firstTriangle(sf::PrimitiveType::Triangles, 3);
		firstTriangle[0] = sf::Vertex(first);
		firstTriangle[1] = sf::Vertex(new1);
		firstTriangle[2] = sf::Vertex(new2);
		newlyCreated.push_back(firstTriangle);

		// Second triangle
		sf::VertexArray secondTriangle(sf::PrimitiveType::Triangles, 3);
		secondTriangle[0] = sf::Vertex(new1);
		secondTriangle[1] = sf::Vertex(second);
		secondTriangle[2] = sf::Vertex(new3);
		newlyCreated.push_back(secondTriangle);

		// Third triangle
		sf::VertexArray thirdTriangle(sf::PrimitiveType::Triangles, 3);
		thirdTriangle[0] = sf::Vertex(new2);
		thirdTriangle[1] = sf::Vertex(new3);
		thirdTriangle[2] = sf::Vertex(third);
		newlyCreated.push_back(thirdTriangle);
	}
	triangles = newlyCreated;
}

int main() {
	int iterations = 0;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sierpinski triangle");

	std::vector<sf::VertexArray> triangles;
	
	sf::Vertex p1({ 0.0f, (float)HEIGHT });	// Bottom left
	sf::Vertex p2({ (float)WIDTH, (float)HEIGHT });	// Bottom right
	sf::Vertex p3({ (float)WIDTH / 2.0f, 0.0f }); // Top

	sf::VertexArray triangle(sf::PrimitiveType::Triangles, 3);
	triangle[0] = p1;
	triangle[1] = p2;
	triangle[2] = p3;
	triangles.push_back(triangle);

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				iterate(triangles, iterations++);
			}
		}

		window.clear();

		for(auto& t : triangles)
		{
			window.draw(t);
		}

		window.display();
	}

	return 0;
}