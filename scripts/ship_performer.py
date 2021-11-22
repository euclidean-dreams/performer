from tchotchke.logger import Logger
from tchotchke.shell import Shell

FOSTER = "foster"
WEBSTER = "webster"
SQUIGS = "squigs"

# change target here
PERFORMER_NAME = WEBSTER

PERFORMER_ADDRESS = PERFORMER_NAME


def ship_executable(shell):
    shell.execute_for_stdout("scp root@ambrose:/root/performer-deployment/cmake-build-release-conductor/performer .")
    shell.execute_for_stdout(
        f"scp ./performer root@{PERFORMER_ADDRESS}:/root/performer"
    )
    shell.execute_for_stdout("rm ./performer")
    shell.execute_for_stdout(
        f"scp ../{PERFORMER_NAME}_config.yml root@{PERFORMER_ADDRESS}:/root/config.yml"
    )


def main():
    logger = Logger()
    with logger.log_uncaught_exceptions():
        shell = Shell(logger)
        ship_executable(shell)
        logger.info("starting performer")
        shell.execute_for_stdout(f"ssh -t root@{PERFORMER_ADDRESS} '/root/performer'")


if __name__ == '__main__':
    main()
