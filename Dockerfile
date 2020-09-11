FROM roboxes/rhel6
COPY ./code/* /app/
RUN gcc /app/tetris.c -o /app/tetris -lncurses
RUN ls /app/

ENV TERM=xterm

RUN /app/tetris
