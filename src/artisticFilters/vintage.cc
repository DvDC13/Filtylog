#include "vintage.hh"

void ApplyFilmGrainEffect(unsigned char* imageData, int width, int height, int noise, double direction)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis_direction(0.0, 2 * M_PI); // Distribution for generating random directions
    std::uniform_real_distribution<> dis_length(0.0, 10.0); // Distribution for generating random vein lengths

    double vein_length = dis_length(gen);
    double vein_intensity = 0.5;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int vein_r = static_cast<int>(vein_intensity * noise);
            int vein_g = static_cast<int>(vein_intensity * noise);
            int vein_b = static_cast<int>(vein_intensity * noise);

            int vein_j = j + static_cast<int>(vein_length * std::cos(direction));
            int vein_i = i + static_cast<int>(vein_length * std::sin(direction));

            if (vein_j >= 0 && vein_j < width && vein_i >= 0 && vein_i < height)
            {
                imageData[(vein_i * width + vein_j) * 3] = std::min(255, imageData[(vein_i * width + vein_j) * 3] + vein_r);
                imageData[(vein_i * width + vein_j) * 3 + 1] = std::min(255, imageData[(vein_i * width + vein_j) * 3 + 1] + vein_g);
                imageData[(vein_i * width + vein_j) * 3 + 2] = std::min(255, imageData[(vein_i * width + vein_j) * 3 + 2] + vein_b);
            }
        }
    }
}

void ApplyVintageFilter(unsigned char* imageData, int width, int height)
{
    ApplySepia(imageData, width, height);
    double distance = ApplyVignetteEffect(imageData, width, height);
    ApplyFilmGrainEffect(imageData, width, height, 5, distance);
}