#include "crossHatch.hh"

void ApplyCrossHatch(unsigned char* imageData, int width, int height)
{
    // Convert the image to grayscale
    ApplyGrayscale(imageData, width, height);

    // Define the line spacing and thickness parameters
    int lineSpacing = 5;  // Spacing between lines
    int lineThickness = 2; // Thickness of each line

    // Iterate over each pixel in the image
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Calculate the line indices for the current pixel
            int lineX = x % lineSpacing;
            int lineY = y % lineSpacing;

            int tmp = lineX;
            
            // Orient the lineX at 45 degrees
            lineX = (lineX + lineY) % lineSpacing;
            
            // Orient the lineY at -45 degrees
            lineY = (tmp - lineY + lineSpacing) % lineSpacing;

            // Check if the pixel lies within a line
            if (lineX < lineThickness || lineY < lineThickness)
            {
                // Darker color for pixels within the line thickness
                imageData[3 * (y * width + x)] = 0;
                imageData[3 * (y * width + x) + 1] = 0;
                imageData[3 * (y * width + x) + 2] = 0;
            }
            else
            {
                // Original color for pixels outside the line thickness
                imageData[3 * (y * width + x)] = imageData[3 * (y * width + x)];
                imageData[3 * (y * width + x) + 1] = imageData[3 * (y * width + x) + 1];
                imageData[3 * (y * width + x) + 2] = imageData[3 * (y * width + x) + 2];
            }
        }
    }
}