from typing import *
import pygame
import sys

LEVELS_LIST = [
    (
        "00000000",
        "00000000",
        "11111102"
    ),
    (
        "000000000",
        "101010102"
    ),
    (
        "0000000000",
        "1000011111",
        "0000111000",
        "1111111121",
        "1111111111"
    ),
    (
        "00000000",
        "10000001",
        "00100001",
        "00000000",
        "00000100",
        "00000000",
        "00100100",
        "00000000",
        "00000000",
        "00000002",
    ),
    (
        "0100000100010000",
        "0100001010010000",
        "0100001010010000",
        "0100001010010000",
        "0111200100011110"
    )
]


GAME_FLAG = True

# Константы окружения
FPS = 60
WIDTH = 1200
HEIGHT = 800
SCREEN_SIZE = (WIDTH, HEIGHT)

# Константы отвечающие за характеристики персонажей
HIGH_PLAYER_SIZE = (10, 60)
HIGH_PLAYER_JUMP_FORCE = 400
HIGH_PLAYER_JUMP_SPEED = 20

MID_PLAYER_SIZE = (10, 30)
MID_PLAYER_JUMP_FORCE = 5

LOW_PLAYER_SIZE = (10, 10)
LOW_PLAYER_JUMP_FORCE = 0
# Константы отвечающие за размер блоков
BLOCK_SIZE = 20

# Константы отвечающие за цвета
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
YELLOW = (225, 225, 0)
PINK = (230, 50, 230)


# Физические константы
FALLING_SPEED = 10

# Константы отвечающие за направление движения
LEFT = -1
RIGHT = 1
STOP = 0
DOWN = 1
UP = -1


class GameObject:
    # Класс родитель всех игровых объектов
    def __init__(self, color: Tuple[int, int, int], size: Tuple[int, int], position: Tuple[int, int]):
        self.color = color

        self.size = size
        self.width, self.height = self.size

        self.position = position
        self.x_pos, self.y_pos = self.position
        self.y_pos -= self.height
        self.position = (self.x_pos, self.y_pos)

        self.body = pygame.Rect(self.position, self.size)

        self.hit_boxes = (
                            pygame.Rect((self.x_pos - 3, self.y_pos - 1), (self.width + 6, 3)),
                            pygame.Rect((self.x_pos - 1, self.y_pos + self.height), (self.width + 2, 3)),
                            pygame.Rect((self.x_pos - 1, self.y_pos), (3, self.height)),
                            pygame.Rect((self.x_pos + self.width, self.y_pos), (3, self.height))
                         )

        self.top_hbox, self.bottom_hbox, self.left_hbox, self.right_hbox = self.hit_boxes

    def draw(self, surface: pygame.Surface):
        pygame.draw.rect(surface, self.color, self.body)
        # for box in self.hit_boxes:
        #    pygame.draw.rect(surface, LIGHT_BLUE, box)


class Block(GameObject):
    # Класс блоков из которых конструируется карта
    def __init__(self, color: Tuple[int, int, int], size: Tuple[int, int] = (10, 10),
                 position: Tuple[int, int] = (0, 0)):
        super().__init__(color, size, position)

    def draw(self, surface: pygame.Surface):
        super().draw(surface)


class MapGrid(pygame.Surface):
    # Класс для разметки игровой карты
    def __init__(self, grid=LEVELS_LIST[0],
                 colors: Tuple[Tuple[int, int, int]] = (BLACK, WHITE, PINK)):
        super().__init__(SCREEN_SIZE)

        self.grid = grid
        self.block_size = (WIDTH // len(grid[0]), HEIGHT // len(grid))
        self.colors = colors
        self.list_of_ground_blocks: list[Block] = list()
        self.list_of_special_blocks: list[Block] = list()

    def draw_on_self(self, env_object: GameObject):
        env_object.draw(self)

    def set_map(self, grid: Tuple[str]):
        self.grid = grid
        self.list_of_ground_blocks = list()
        self.list_of_special_blocks = list()
        self.place_blocks()

    def place_blocks(self):
        for str_i in range(len(self.grid)):
            for block_i in range(len(self.grid[str_i])):
                current_block_id = int(self.grid[str_i][block_i])
                current_color = self.colors[current_block_id]

                pos_x = block_i * self.block_size[0]
                pos_y = str_i * self.block_size[1]

                current_block = Block(current_color, self.block_size, (pos_x, pos_y + self.block_size[1]))
                if current_block_id == 1:
                    self.list_of_ground_blocks.append(current_block)
                if current_block_id == 2:
                    self.list_of_special_blocks.append(current_block)
                self.draw_on_self(current_block)

    def get_list_of_ground_blocks(self):
        return self.list_of_ground_blocks

    def get_list_of_special_blocks(self):
        return self.list_of_special_blocks


class GameArea:
    # Класс игровой области
    def __init__(self, screen_size: Tuple[int, int], color: Tuple[int, int, int] = BLACK):
        self.screen_size = screen_size
        self.color = color
        self.user_area = pygame.display.set_mode(self.screen_size)
        self.fill()

    def draw_on_self(self, env_object: GameObject):
        env_object.draw(self.user_area)

    def blit_on_self(self, source: MapGrid, dest: Tuple[int, int]):
        self.user_area.blit(source, dest)

    def fill(self):
        self.user_area.fill(self.color)


class Player(GameObject):
    # Класс игрового персонажа
    def __init__(self, color: Tuple[int, int, int], size: Tuple[int, int], position: Tuple[int, int] = (0, 0),
                 jump_force: int = HIGH_PLAYER_JUMP_FORCE, speed: int = 5):
        super().__init__(color, size, position)

        self.jump_force = jump_force
        self.speed = speed

    def draw(self, surface: pygame.Surface):
        super().draw(surface)

    def move(self, direction_x: int, direction_y: int, speed_x: int, speed_y: int = FALLING_SPEED):
        self.body.move_ip(speed_x * direction_x, speed_y * direction_y)
        for box in self.hit_boxes:
            box.move_ip(speed_x * direction_x, speed_y * direction_y)

    def update_jump(self):
        self.update_position(STOP, UP, STOP, HIGH_PLAYER_JUMP_SPEED)

    def update_position(self, direction_x: int, direction_y: int, speed_x: int, speed_y: int = FALLING_SPEED):
        self.x_pos += speed_x * direction_x
        self.y_pos += speed_y * direction_y
        self.position = (self.x_pos, self.y_pos)

        self.move(direction_x, direction_y, speed_x, speed_y)

    def set_position(self, position: Tuple[int, int]):
        self.update_position(1, 1, position[0] - self.x_pos, position[1] - self.y_pos)
        self.position = position
        self.x_pos, self.y_pos = position

    def is_on_ground(self, env_block: Block):
        return self.bottom_hbox.colliderect(env_block.top_hbox)

    def is_collide_wall(self, env_block: Block):
        if self.right_hbox.colliderect(env_block.left_hbox):
            return LEFT
        elif self.left_hbox.colliderect(env_block.right_hbox):
            return RIGHT
        else:
            return STOP

    def is_collide_ceiling(self, env_block: Block):
        return self.top_hbox.colliderect(env_block.bottom_hbox)

    def is_finished(self, env_block: Block):
        for box_i in self.hit_boxes:
            for box_j in env_block.hit_boxes:
                if box_i.colliderect(box_j):
                    return 1
        return 0


class Game:
    def __init__(self):

        # Переменная направления движения (по горизонтали)
        self.move_direction_x = STOP
        self.move_direction_y = STOP

        # Переменные, отвечающие за движения (по вертикали)
        self.jump_flag = False
        self.cur_jump_height = 0
        self.falling_flag = True

        # Переменная, которая отвечает за отталкивание от стены при столкновении
        self.repulsion_ratio = 0

        self.last_event = None

        self.clock = pygame.time.Clock()
        self.screen = GameArea(SCREEN_SIZE)

        self.game_map = MapGrid()
        self.game_map.place_blocks()
        self.ground_blocks = self.game_map.get_list_of_ground_blocks()
        self.special_blocks = self.game_map.get_list_of_special_blocks()

        self.start_position = self.ground_blocks[0].body.midtop
        self.main_player = Player(YELLOW, HIGH_PLAYER_SIZE, self.start_position)

        self.cur_level_index = 0

    def load_level(self, level_index: int):
        cur_level_index = level_index
        self.game_map = MapGrid(grid=LEVELS_LIST[cur_level_index])
        self.game_map.place_blocks()
        self.ground_blocks = self.game_map.get_list_of_ground_blocks()
        self.special_blocks = self.game_map.get_list_of_special_blocks()
        self.start_position = (self.ground_blocks[0].top_hbox.midtop[0],
                               self.ground_blocks[0].top_hbox.midtop[1] - self.main_player.height * 2)
        self.main_player.set_position(self.start_position)

    def restart(self):
        self.load_level(self.cur_level_index)

    def handle_collisions(self):
        self.falling_flag = True

        for block in self.ground_blocks:
            if self.main_player.is_on_ground(block):
                self.falling_flag = False
            if self.main_player.is_collide_ceiling(block):
                self.jump_flag = False

        for block in self.special_blocks:
            if self.main_player.is_finished(block):
                self.cur_level_index += 1
                if self.cur_level_index == len(LEVELS_LIST):
                    sys.exit()
                self.load_level(self.cur_level_index)

        for block in self.ground_blocks:
            self.repulsion_ratio = self.main_player.is_collide_wall(block)
            if self.repulsion_ratio != STOP:
                break

    def handle_falling(self):
        if self.falling_flag:
            self.move_direction_y = DOWN
        else:
            self.move_direction_y = STOP

    def handle_pygame_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key in (pygame.K_LEFT, pygame.K_h):
                    self.move_direction_x = LEFT
                    self.last_event = pygame.K_LEFT

                elif event.key in (pygame.K_RIGHT, pygame.K_l):
                    self.move_direction_x = RIGHT
                    self.last_event = pygame.K_RIGHT

                if event.key == pygame.K_SPACE and not self.falling_flag:
                    self.jump_flag = True
                    self.cur_jump_height = 0

            if event.type == pygame.KEYUP:
                if event.key in (pygame.K_LEFT, pygame.K_h) and self.last_event == pygame.K_LEFT:
                    self.move_direction_x = STOP
                elif event.key in (pygame.K_RIGHT, pygame.K_l) and self.last_event == pygame.K_RIGHT:
                    self.move_direction_x = STOP

    def handle_jump(self):
        if self.jump_flag:
            self.cur_jump_height += HIGH_PLAYER_JUMP_SPEED
            self.main_player.update_jump()
            if self.cur_jump_height >= self.main_player.jump_force:
                self.jump_flag = False

    def update_screen_info(self):
        self.screen.fill()
        self.screen.blit_on_self(self.game_map, (0, 0))
        self.main_player.update_position(self.move_direction_x + abs(self.move_direction_x) * self.repulsion_ratio,
                                         self.move_direction_y, self.main_player.speed, FALLING_SPEED)
        self.screen.draw_on_self(self.main_player)
        pygame.display.update()

        self.clock.tick(FPS)

    def mainloop(self):
        while GAME_FLAG:
            if self.main_player.y_pos >= HEIGHT:
                self.restart()
            self.handle_collisions()
            self.handle_falling()
            self.handle_pygame_events()
            self.handle_jump()
            self.update_screen_info()


if __name__ == '__main__':
    game = Game()
    game.mainloop()
