#include <SFML/Graphics.hpp>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

void iterate(std::vector<sf::VertexArray>& triangles)
{
	std::vector<sf::VertexArray> newlyCreated;

	for(auto& t : triangles)
	{
		sf::Vector2f& first = t[0].position;
		sf::Vector2f& second = t[1].position;
		sf::Vector2f& third = t[2].position;

		// Calculating positions
		sf::Vector2f new1((first.x + second.x) * 0.5f, (first.y + second.y) * 0.5f);
		sf::Vector2f new2((first.x + third.x) * 0.5f, (first.y + third.y) * 0.5f);
		sf::Vector2f new3((second.x + third.x) * 0.5f, (second.y + third.y) * 0.5f);

		// First triangle
		sf::VertexArray firstTriangle(sf::PrimitiveType::Points, 3);
		firstTriangle[0] = sf::Vertex(first);
		firstTriangle[1] = sf::Vertex(new1);
		firstTriangle[2] = sf::Vertex(new2);
		newlyCreated.push_back(firstTriangle);

		// Second triangle
		sf::VertexArray secondTriangle(sf::PrimitiveType::Points, 3);
		secondTriangle[0] = sf::Vertex(new1);
		secondTriangle[1] = sf::Vertex(second);
		secondTriangle[2] = sf::Vertex(new3);
		newlyCreated.push_back(secondTriangle);

		// Third triangle
		sf::VertexArray thirdTriangle(sf::PrimitiveType::Points, 3);
		thirdTriangle[0] = sf::Vertex(new2);
		thirdTriangle[1] = sf::Vertex(new3);
		thirdTriangle[2] = sf::Vertex(third);
		newlyCreated.push_back(thirdTriangle);
	}
	triangles = newlyCreated;
}

int main() 
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sierpinski triangle");

	std::vector<sf::VertexArray> triangles;

	sf::VertexArray triangle(sf::PrimitiveType::Points, 3);
	triangle[0] = sf::Vertex({ 0.0f, (float)HEIGHT });			// Bottom left
	triangle[1] = sf::Vertex({ (float)WIDTH, (float)HEIGHT });	// Bottom right
	triangle[2] = sf::Vertex({ (float)WIDTH / 2.0f, 0.0f });	// Top
	triangles.push_back(triangle);

	while(window.isOpen()) 
	{
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				iterate(triangles);
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