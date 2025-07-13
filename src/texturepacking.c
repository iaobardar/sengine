
/*
Steps to work on to integrate this into the sprite renderer.
1. Get it rendering without a texture,
2. with a single texture they all share,
3. with the sub textures,
*/

#include <stdlib.h>
#include <stdio.h>
#include "texturepacking.h"
#include "texture.h"

static inline size_t left(size_t i) {return i * 2 + 1;}
static inline size_t right(size_t i) {return i * 2 + 2;}
static inline size_t parent(size_t i) {return (i - 1) / 2;}

#define SWAP(a, b) size_t temp = (a); (a) = (b); (b) = temp;

struct packed_texture pack_textures(struct texture* textures, size_t count, size_t max_width)
{
   // blit all the textures into one big texture sorted into rows by height. Very naive algorithm.
   puts("Packing:");

   // heap sort the textures
   size_t* sorted = malloc(count * sizeof(size_t));
   assert(sorted);
   for (size_t i = 0; i < count; ++i)
   {
      sorted[i] = i;
      printf("%zu: (%zu:%zu)\n", i, textures[i].width, textures[i].height);
   }

   // build heap by sifting toward root
   for (size_t i = 1; i < count; ++i)
   {
      size_t s = i;
      while (s > 0 && textures[sorted[s]].height < textures[sorted[parent(s)]].height)
      {
         SWAP(sorted[s], sorted[parent(s)]);
         s = parent(s);
      }
   }

   puts("built heap");
   for (size_t i = 0; i < count; ++i)
   {
      printf("%zu: (%zu:%zu)\n", sorted[i], textures[sorted[i]].width, textures[sorted[i]].height);
   }

   // sort by pulling everything out of the heap
   for (size_t heap_end = count - 1; heap_end > 0; --heap_end)
   {
      SWAP(sorted[0], sorted[heap_end]);

      size_t sift = 0;
      while (1)
      {
         size_t LC = left(sift)  < heap_end && textures[sorted[left(sift) ]].height < textures[sorted[sift]].height;
         size_t RC = right(sift) < heap_end && textures[sorted[right(sift)]].height < textures[sorted[sift]].height;

         if (LC)
         {
            if (RC && textures[sorted[right(sift)]].height < textures[sorted[left(sift)]].height)
            {
               SWAP(sorted[sift], sorted[right(sift)]);
               sift = right(sift);
            }
            else
            {
               SWAP(sorted[sift], sorted[left(sift)]);
               sift = left(sift);
            }
         }
         else
         {
            if (RC)
            {
               SWAP(sorted[sift], sorted[right(sift)]);
               sift = right(sift);
            }
            else
            {
               break; // break out of the sifting
            }
         }
      }

      puts("pulled out");
      for (size_t i = 0; i < count; ++i)
      {
         printf("%zu: (%zu:%zu)\n", sorted[i], textures[sorted[i]].width, textures[sorted[i]].height);
      }
   }

   puts("sorted");
   for (size_t i = 0; i < count; ++i)
   {
      printf("%zu: (%zu:%zu)\n", sorted[i], textures[sorted[i]].width, textures[sorted[i]].height);
   }

   // add each in order to the packed texture naively
   struct packed_texture pack = {
      .count_sub_textures = count,
      .sub_textures = malloc(count * sizeof(struct sub_texture_info)),
   };
   assert(pack.sub_textures);

   puts("building pack");

   size_t y = 0;
   size_t si = 0;
   while (1)
   {
      if (si >= count) break;
      size_t next_y = y + textures[sorted[si]].height;
      size_t x = 0;
      assert(textures[sorted[si]].width <= max_width);
      while (1)
      {
         if (si >= count) break;
         size_t next_x = x + textures[sorted[si]].width;

         if (next_x >= max_width) break; // COULD MAKE THIS BETTER BY LOOKING AHEAD FOR OTHER ONES THAT WOULD FIT.

         pack.sub_textures[sorted[si]].x = x;
         pack.sub_textures[sorted[si]].y = y;
         pack.sub_textures[sorted[si]].width  = textures[sorted[si]].width;
         pack.sub_textures[sorted[si]].height = textures[sorted[si]].height;

         ++si;
         x = next_x;
      }
      y = next_y;
   }
   
   // copy the textures to their place in the packed texture.
   pack.container_texture = alloc_texture(max_width, y);
   for (size_t i = 0; i < count; ++i)
   {
      printf("%zu: (%zu,%zu - %zu:%zu)\n", i, pack.sub_textures[i].x, pack.sub_textures[i].y, pack.sub_textures[i].width, pack.sub_textures[i].height);
      blit_texture(pack.sub_textures[i].width, pack.sub_textures[i].height, &pack.container_texture, pack.sub_textures[i].x, pack.sub_textures[i].y, &textures[i], 0, 0);
   }

   free(sorted);
   return pack;
}

#undef SWAP
